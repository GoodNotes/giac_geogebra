#include "GiacBridge.h"
#include "GenBridge.hpp"
#include "giac.h"
#include <string>
#include <vector>
#include <mutex>

#define FAIL_AND_TERMINATE(msg) \
    do { \
        lastError = msg; \
        std::cerr << "[FATAL] " << __FUNCTION__ << ": " << msg << std::endl; \
        std::terminate(); \
    } while (0)

using namespace std;


void test(void)
{
    giac::context ct;
    string line;
    giac::gen g;
    int n = 1; // in giac this starts from 0
    g=giac::gen("[1,2,3]",&ct);
    cout << giac::eval(g,1,&ct) << endl;
    cout << g._VECTptr << endl;
    cout << g._VECTptr->size() << endl; 
}

extern "C" void GiacBridge_logInit() {
    std::cout << "[DEBUG] >>> GiacBridge manually initialized <<<" << std::endl;
}

extern "C" int giacBridgePing() {
    std::cerr << "[DEBUG] giacBridgePing was called" << std::endl;
    return 42;
}

thread_local string lastError;

const char* getLastError(void) {
    return lastError.empty() ? nullptr : lastError.c_str();
}

void clearLastError(void) {
    lastError.clear();
}

// Context functions

__attribute__ ((visibility ("default"))) void* Context_create(void) {
    std::cout << "[DEBUG] " << __FUNCTION__ << " called" << "\n";
    try {
        return new ContextBridge();
    } catch (...) {
        FAIL_AND_TERMINATE("Context_create failed.");
    }
}

__attribute__ ((visibility ("default"))) void Context_destroy(void* ctx) {
    std::cout << "[DEBUG] " << __FUNCTION__ << " called" << "\n";
    delete static_cast<ContextBridge*>(ctx);
}

// Gen functions

void* Gen_createFromString(void* ctx, const char* expression) {
    std::cout << "[DEBUG] " << __FUNCTION__ << " called with ctx: " << ctx << " and expression " << expression << "\n";
    try {
        return new GenBridge(string(expression), *static_cast<ContextBridge*>(ctx));
    } catch (...) {
        FAIL_AND_TERMINATE("Gen_createFromString failed.");
    }
}

void* Gen_createFromInt(void* ctx, int value) {
    std::cout << "[DEBUG] " << __FUNCTION__ << " called with ctx: " << ctx << " and value " << value << "\n";
    try {
        return new GenBridge(new giac::gen(value));
    } catch (...) {
        FAIL_AND_TERMINATE("Gen_createFromInt failed.");
    }
}

void* Gen_createFromDouble(void* ctx, double value) {
    std::cout << "[DEBUG] " << __FUNCTION__ << " called with ctx: " << ctx << " and value " << value << "\n";
    try {
        return new GenBridge(new giac::gen(value));
    } catch (...) {
        FAIL_AND_TERMINATE("Gen_createFromDouble failed.");
    }
}

void Gen_destroy(void* gen) {
    std::cout << "[DEBUG] " << __FUNCTION__ << " called " << "\n";
    delete static_cast<GenBridge*>(gen);
}

void* Gen_eval(void* ctx, void* gen, int level) {
    std::cout << "[DEBUG] " << __FUNCTION__ << " called with ctx: " << ctx << " gen " << gen << " and level " << level << "\n";
    try {
        return static_cast<GenBridge*>(gen)->eval(level, *static_cast<ContextBridge*>(ctx));
    } catch (...) {
        FAIL_AND_TERMINATE("Gen_eval failed.");
    }
}

const char* Gen_print(void* ctx, void* gen) {
    std::cout << "[DEBUG] " << __FUNCTION__ << " called with ctx: " << ctx << " gen " << gen << "\n";
    try {
        static thread_local string result;
        result = static_cast<GenBridge*>(gen)->print(*static_cast<ContextBridge*>(ctx));
        return result.c_str();
    } catch (...) {
        FAIL_AND_TERMINATE("Gen_print failed.");
    }
}

int Gen_type(void* gen) {
    std::cout << "[DEBUG] " << __FUNCTION__ << " called with gen " << gen << "\n";
    try {
        return static_cast<GenBridge*>(gen)->type();
    } catch (...) {
        FAIL_AND_TERMINATE("Gen_type failed.");
    }
}

int Gen_length(void* gen) {
    std::cout << "[DEBUG] " << __FUNCTION__ << " called with gen " << gen << "\n";
    try {
        return static_cast<GenBridge*>(gen)->lenght();
    } catch (...) {
        FAIL_AND_TERMINATE("Gen_length failed.");
    }
}

int Gen_isNull(void* gen) {
    std::cout << "[DEBUG] " << __FUNCTION__ << " called with gen " << gen << "\n";
    try {
        return static_cast<GenBridge*>(gen)->isNull();
    } catch (...) {
        FAIL_AND_TERMINATE("Gen_isNull failed.");
    }
}

int Gen_equalSign(void* a, void* b) {
    std::cout << "[DEBUG] " << __FUNCTION__ << " called with gen a " << a << "and b " << b << "\n";
    try {
        return static_cast<GenBridge*>(a)->equalSign(*static_cast<GenBridge*>(b));
    } catch (...) {
        FAIL_AND_TERMINATE("Gen_equalSign failed.");
    }
}

void Gen_selfEval(void* ctx, void* gen, int level) {
    std::cout << "[DEBUG] " << __FUNCTION__ << " called with ctx: " << ctx << " gen " << gen << " and level " << level << "\n";
    try {
        static_cast<GenBridge*>(gen)->selfEval(level, *static_cast<ContextBridge*>(ctx));
    } catch (...) {
        FAIL_AND_TERMINATE("Gen_selfEval failed.");
    }
}

void Gen_resetTimeout(void* gen) {
    std::cout << "[DEBUG] " << __FUNCTION__ << " called with gen " << gen << "\n";
    try {
        static_cast<GenBridge*>(gen)->resetTimeout();
    } catch (...) {
        FAIL_AND_TERMINATE("Gen_resetTimeout failed.");
    }
}

void Gen_getListVector(void* gen, void*** list, int* size) {
    std::cout << "[DEBUG] " << __FUNCTION__ << " called with gen " << gen << "\n";
    try {
        static thread_local vector<GenBridge*> result;
        result.clear();
        static_cast<GenBridge*>(gen)->getListVector(result);
        *size = result.size();
        *list = reinterpret_cast<void**>(result.data());
    } catch (...) {
        FAIL_AND_TERMINATE("Gen_getListVector failed.");
    }
}

int Gen_getListSize(void* gen) {
    std::cout << "[DEBUG] " << __FUNCTION__ << " called with gen " << gen << "\n";
    try {
        int ret = static_cast<GenBridge*>(gen)->lenght();
        std::cout << "[DEBUG] " << __FUNCTION__ << " returning " << ret << "\n";
        return ret;
    } catch (...) {
        FAIL_AND_TERMINATE("Gen_getListSize failed.");
    }
}

void* Gen_getListElement(void* ctx, void* gen, int index) {
    std::cout << "[DEBUG] " << __FUNCTION__ << " called with context " << ctx << " gen " << gen << " and index " << index << "\n";
    try {
        vector<GenBridge*> list;
        static_cast<GenBridge*>(gen)->getListVector(list);

        if (index < 0 || index >= static_cast<int>(list.size())) {
            FAIL_AND_TERMINATE("Gen_getListElement: Index out of bounds.");
        }

        return list[index]; // Return pointer to existing GenBridge
    } catch (...) {
        FAIL_AND_TERMINATE("Gen_getListElement failed.");
    }
}


const char* Gen_lname(void* gen) {
    std::cout << "[DEBUG] " << __FUNCTION__ << " called with gen " << gen << "\n";
    try {
        static thread_local string result;
        ContextBridge dummyContext; // you may want to adjust this
        result = static_cast<GenBridge*>(gen)->lname(dummyContext)->print(dummyContext);
        return result.c_str();
    } catch (...) {
        FAIL_AND_TERMINATE("Gen_lname failed.");
    }
}

void* Gen_left(void* ctx, void* gen) {
    std::cout << "[DEBUG] " << __FUNCTION__ << " called with ctx: " << ctx << " gen " << gen << "\n";
    try {
        return static_cast<GenBridge*>(gen)->left(*static_cast<ContextBridge*>(ctx));
    } catch (...) {
        FAIL_AND_TERMINATE("Gen_left failed.");
    }
}

void* Gen_right(void* ctx, void* gen) {
    std::cout << "[DEBUG] " << __FUNCTION__ << " called with ctx: " << ctx << " gen " << gen << "\n";
    try {
        return static_cast<GenBridge*>(gen)->right(*static_cast<ContextBridge*>(ctx));
    } catch (...) {
        FAIL_AND_TERMINATE("Gen_right failed.");
    }
}

void* Gen_canonicalForm(void* ctx, void* gen) {
    std::cout << "[DEBUG] " << __FUNCTION__ << " called with ctx: " << ctx << " gen " << gen << "\n";
    try {
        return static_cast<GenBridge*>(gen)->canonicalForm(*static_cast<ContextBridge*>(ctx));
    } catch (...) {
        FAIL_AND_TERMINATE("Gen_canonicalForm failed.");
    }
}

void* Gen_regroup(void* ctx, void* gen) {
    std::cout << "[DEBUG] " << __FUNCTION__ << " called with ctx: " << ctx << " gen " << gen << "\n";
    try {
        return static_cast<GenBridge*>(gen)->regroup(*static_cast<ContextBridge*>(ctx));
    } catch (...) {
        FAIL_AND_TERMINATE("Gen_regroup failed.");
    }
}

void* Gen_simplify(void* ctx, void* gen) {
    std::cout << "[DEBUG] " << __FUNCTION__ << " called with ctx: " << ctx << " gen " << gen << "\n";
    try {
        return static_cast<GenBridge*>(gen)->simplify(*static_cast<ContextBridge*>(ctx));
    } catch (...) {
        FAIL_AND_TERMINATE("Gen_simplify failed.");
    }
}

void* Gen_add(void* ctx, void* a, void* b) {
    std::cout << "[DEBUG] " << __FUNCTION__ << " called with ctx: " << ctx << " gen a " << a << "and b " << b << "\n";
    try {
        return static_cast<GenBridge*>(a)->operator+(*static_cast<GenBridge*>(b));
    } catch (...) {
        FAIL_AND_TERMINATE("Gen_add failed.");
    }
}

void* Gen_sub(void* ctx, void* a, void* b) {
    std::cout << "[DEBUG] " << __FUNCTION__ << " called with ctx: " << ctx << " gen a " << a << "and b " << b << "\n";
    try {
        return static_cast<GenBridge*>(a)->operator-(*static_cast<GenBridge*>(b));
    } catch (...) {
        FAIL_AND_TERMINATE("Gen_sub failed.");
    }
}

void* Gen_mul(void* ctx, void* a, void* b) {
    std::cout << "[DEBUG] " << __FUNCTION__ << " called with ctx: " << ctx << " gen a " << a << "and b " << b << "\n";
    try {
        return static_cast<GenBridge*>(a)->operator*(*static_cast<GenBridge*>(b));
    } catch (...) {
        FAIL_AND_TERMINATE("Gen_mul failed.");
    }
}

void* Gen_div(void* ctx, void* a, void* b) {
    std::cout << "[DEBUG] " << __FUNCTION__ << " called with ctx: " << ctx << " gen a " << a << "and b " << b << "\n";
    try {
        return static_cast<GenBridge*>(a)->operator/(*static_cast<GenBridge*>(b));
    } catch (...) {
        FAIL_AND_TERMINATE("Gen_div failed.");
    }
}

void* Gen_negate(void* ctx, void* gen) {
    std::cout << "[DEBUG] " << __FUNCTION__ << " called with ctx: " << ctx << " gen " << gen << "\n";
    try {
        return static_cast<GenBridge*>(gen)->operator-();
    } catch (...) {
        FAIL_AND_TERMINATE("Gen_negate failed.");
    }
}
