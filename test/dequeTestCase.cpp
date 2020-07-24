#include "dequeTestCase.h"

#include "deque.h"

namespace mySTL {
    void DequeTestCase::testAll() {
        printf("\nDequeTestCase start!\n");
        testCase1();
        testCase2();
        printf("DequeTestCase pass!\n");
    }

    void DequeTestCase::testCase1() {
        deque<int, Allocator<int>, 4> dq1(10, 2);
        deque<int>                    dq2;
        deque<int>                    dq3(2, 2);
        if (dq1.size() != 10 || dq2.size() != 0 || dq3.size() != 2) {
            error_msg("DequeTestCase1 stage 1");
        }
    }
    void DequeTestCase::testCase2() {}
}  // namespace mySTL