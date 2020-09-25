#include <pthread.h>

#include "safe.h"
class CAPABILITY("mutex") Mutex {
public:
    Mutex() { pthread_mutex_init(&mutex_, NULL); }
    void lock() ACQUIRE() { pthread_mutex_lock(&mutex_); }
    void unlock() RELEASE() { pthread_mutex_unlock(&mutex_); }
    ~Mutex() { pthread_mutex_destroy(&mutex_); }

private:
    pthread_mutex_t mutex_;
};