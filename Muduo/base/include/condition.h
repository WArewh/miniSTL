#ifndef BASE_CONDITION_H_
#define BASE_CONDITION_H_

#include "mutex.h"

namespace furry {
    //条件变量封装
    class condition : noncopyable {
    public:
        condition(mutexLock& mutex);
        ~condition();
        void wait();
        void notify();
        void notifyAll();

    private:
        mutexLock&     m_mutexLock;
        pthread_cond_t m_condition;
    };
}  // namespace furry

#endif