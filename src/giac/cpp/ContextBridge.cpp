#include "ContextBridge.hpp"
#include "giac.h"
#include <pthread.h>
#include <stdexcept>

ContextBridge::ContextBridge() {
#ifdef HAVE_LIBPTHREAD
    static pthread_mutex_t context_mutex = PTHREAD_MUTEX_INITIALIZER;
    if (pthread_mutex_lock(&context_mutex) != 0) {
        throw std::runtime_error("Failed to lock context mutex");
    }
#endif
    try {
        c = new giac::context();
    } catch (...) {
#ifdef HAVE_LIBPTHREAD
        pthread_mutex_unlock(&context_mutex);
#endif
        throw;
    }
#ifdef HAVE_LIBPTHREAD
    if (pthread_mutex_unlock(&context_mutex) != 0) {
        throw std::runtime_error("Failed to unlock context mutex");
    }
#endif
}

ContextBridge::~ContextBridge() {
    static pthread_mutex_t context_mutex2 = PTHREAD_MUTEX_INITIALIZER;
#ifdef HAVE_LIBPTHREAD
    if (pthread_mutex_lock(&context_mutex2) != 0) {
        throw std::runtime_error("Failed to lock context mutex");
    }
#endif
    delete c;
#ifdef HAVE_LIBPTHREAD
    if (pthread_mutex_unlock(&context_mutex2) != 0) {
        throw std::runtime_error("Failed to unlock context mutex");
    }
#endif
}
