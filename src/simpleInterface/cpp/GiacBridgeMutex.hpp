#ifndef GOODNOTES_GIAC_BRIDGE_MUTEX_HPP
#define GOODNOTES_GIAC_BRIDGE_MUTEX_HPP

#ifdef HAVE_LIBPTHREAD
#include <pthread.h>
#include <stdexcept>

// All bridge entry points share this recursive mutex. Some GenBridge methods
// create another GenBridge while evaluating, so a plain mutex would deadlock.
pthread_mutex_t & giac_bridge_mutex();
#endif

class GiacBridgeLock {
public:
    GiacBridgeLock() {
#ifdef HAVE_LIBPTHREAD
        if (pthread_mutex_lock(&giac_bridge_mutex()) != 0)
            throw std::runtime_error("Failed to lock Giac bridge mutex");
#endif
    }

    ~GiacBridgeLock() {
#ifdef HAVE_LIBPTHREAD
        pthread_mutex_unlock(&giac_bridge_mutex());
#endif
    }

private:
    GiacBridgeLock(const GiacBridgeLock &);
    GiacBridgeLock & operator=(const GiacBridgeLock &);
};

#endif
