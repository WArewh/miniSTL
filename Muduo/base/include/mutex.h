#ifndef BASE_MUTEX_H_
#define BASE_MUTEX_H_

#include <pthread.h>

#include <cassert>

#include "noncopyable.h"

namespace furry {

    // mutex的封装,未完工
    class mutexLock : noncopyable {

    public:
        using thread_id = pid_t;

    public:
        mutexLock();
        ~mutexLock();
        void lock();    //内部使用
        void unlock();  //内部使用

    public:
        bool isLockedByThisThread();

        pthread_mutex_t* getPthreadMutex();

    private:
        pthread_mutex_t m_mutex;
        thread_id       m_holder;
    };
}  // namespace furry

namespace furry {
    //管理mutexLock
    class mutexLockGuard : noncopyable {

    public:
        explicit mutexLockGuard(mutexLock& mutex);
        ~mutexLockGuard();

    private:
        mutexLock& m_mutexLock;
    };

}  // namespace furry

#endif