#include "include/mutex.h"

namespace furry {

    mutexLock::mutexLock() : m_holder(0) { pthread_mutex_init(&m_mutex, NULL); }

    mutexLock::~mutexLock() {
        assert(m_holder == 0);
        pthread_mutex_destroy(&m_mutex);
    }

    void mutexLock::lock() { pthread_mutex_lock(&m_mutex); }

    void mutexLock::unlock() { pthread_mutex_unlock(&m_mutex); }

    bool isLockedByThisThread() { return true; }

    pthread_mutex_t* mutexLock::getPthreadMutex() { return &m_mutex; }
}  // namespace furry


namespace furry {
    mutexLockGuard::mutexLockGuard(mutexLock& mutex) : m_mutexLock(mutex) {
        m_mutexLock.lock();
    }

    mutexLockGuard::~mutexLockGuard() { m_mutexLock.unlock(); }

//缺少变量名
#define mutexLockGuard(x) static_assert(false, "miss guard var name")
}  // namespace furry
