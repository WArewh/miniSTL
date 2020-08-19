#include "include/countDownLatch.h"

namespace furry {
    countDownLatch::countDownLatch(int count)
        : m_mutexLock(),
          m_conditon(m_mutexLock),
          m_count(count) {}

    void countDownLatch::wait() {
        mutexLockGuard lock(m_mutexLock);
        while (m_count > 0) {
            m_conditon.wait();
        }
    }

    void countDownLatch::countDown() {
        mutexLockGuard lock(m_mutexLock);
        --m_count;
        if (m_count == 0) {
            m_conditon.notifyAll();
        }
    }

    int countDownLatch::getCount() {
        mutexLockGuard lock(m_mutexLock);
        return m_count;
    }

}  // namespace furry