#include "GeoGebraCAS.h"
//#include "ContextBridge.hpp"
#include "GenBridge.hpp"
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

context ct;

extern "C" {
    EXPORT void initializeCAS() { return; }
    EXPORT string evaluateCAS(string command) {
        gen e(string(command), &ct);
        try {
            //ContextBridge *cb = new ContextBridge();
            //GenBridge* gb = new GenBridge(command, *cb);
            //return gb->eval(1, *cb)->print(*cb);
            return giac::print(giac::eval(e, 1, &ct), &ct);
            } catch (std::runtime_error & err) {
            cerr << err.what() << endl;
            }
        }
    }
