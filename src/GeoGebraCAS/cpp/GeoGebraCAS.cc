#include "GeoGebraCAS.h"
#include <stdexcept>
#include <giac.h>

using namespace std;
using namespace giac;

#ifndef _WIN32
#define EXPORT __attribute__((visibility("default")))
__attribute__((constructor))
static void initializer(void) { }
__attribute__((destructor))
static void finalizer(void) { }
#else
#define EXPORT
#endif

context *ct;

extern "C" {
    EXPORT void initializeCAS() { ct = new context(); }
    EXPORT void clearContextCAS() { delete ct;}
    EXPORT void clearGlobalVars() { giac::release_globals(); }
    EXPORT string evaluateCAS(string command) {
        gen e(string(command), ct);
        try {
            auto s = giac::print(giac::eval(e, ct), ct);
            e.delete_gen();
            return s;
            } catch (std::runtime_error & err) {
            cerr << err.what() << endl;
            }
        }
}
