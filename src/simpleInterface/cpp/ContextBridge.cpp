#include "ContextBridge.hpp"
#include "giac.h"
#include "GiacBridgeMutex.hpp"
#include <pthread.h>
#include <stdexcept>

#ifdef HAVE_LIBPTHREAD
pthread_mutex_t & giac_bridge_mutex() {
    struct RecursiveMutex {
        pthread_mutex_t mutex;
        RecursiveMutex() {
            pthread_mutexattr_t attributes;
            if (pthread_mutexattr_init(&attributes) != 0 ||
                pthread_mutexattr_settype(&attributes, PTHREAD_MUTEX_RECURSIVE) != 0 ||
                pthread_mutex_init(&mutex, &attributes) != 0) {
                throw std::runtime_error("Failed to create Giac bridge mutex");
            }
            pthread_mutexattr_destroy(&attributes);
        }
    };
    static RecursiveMutex * gate = new RecursiveMutex();
    return gate->mutex;
}
#endif

ContextBridge::ContextBridge() {
    GiacBridgeLock lock;
    c = new giac::context();
}

ContextBridge::~ContextBridge() {
    GiacBridgeLock lock;
    delete c;
}
