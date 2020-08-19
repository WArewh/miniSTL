#ifndef BASE_COUNTDOWNLATCH_H_
#define BASE_COUNTDOWNLATCH_H_

#include "condition.h"

namespace furry {
    // 倒计时器
    class countDownLatch {
    public:
        explicit countDownLatch(int count);
        void wait();
        void countDown();
        int  getCount();

    private:
        //顺序很重要,因为condition需要mutexlock
        mutexLock m_mutexLock;
        condition m_conditon;
        int       m_count;
    };
}  // namespace furry

#endif