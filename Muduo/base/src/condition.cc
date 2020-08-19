#include "include/condition.h"

namespace furry {
    condition::condition(mutexLock& mutex_lock) : m_mutexLock(mutex_lock) {
        pthread_cond_init(&m_condition, NULL);
    }

    condition::~condition() { pthread_cond_destroy(&m_condition); }

    void condition::wait() {
        pthread_cond_wait(&m_condition, m_mutexLock.getPthreadMutex());
    }
    void condition::notify() { pthread_cond_signal(&m_condition); }

    void condition::notifyAll() { pthread_cond_broadcast(&m_condition); }
}  // namespace furry