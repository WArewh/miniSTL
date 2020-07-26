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
        for (auto iter = dq1.begin(); iter != dq1.end(); ++iter) {
            if (*iter != 2) {
                error_msg("DequeTestCase1 stage 2");
            }
        }
        dq1.clear();
        if (dq1.size() != 0) {
            error_msg("DequeTestCase1 stage 3");
        }
    }
    void DequeTestCase::testCase2() {
        deque<int, Allocator<int>, 4> dq1;
        deque<int, Allocator<int>, 4> dq2;
        for (int i = 0; i < 5; ++i) {
            dq1.push_back(i);
            dq2.push_front(i);
        }
        for (int i = 5; i < 20; ++i) {
            dq1.push_back(i);
            dq2.push_front(i);
        }
        int i = 0;
        for (auto iter = dq1.begin(); iter != dq1.end(); ++iter, ++i) {
            if (*iter != i) {
                error_msg("DequeTestCase2 stage 1");
            }
        }
        dq1.clear();
        if (dq1.size() != 0) {
            error_msg("DequeTestCase2 stage 2");
        }
        for (int i = 20; i < 40; ++i) {
            dq1.push_back(i);
        }
        for (int i = 19; i >= 0; --i) {
            dq1.push_front(i);
        }
        i = 0;
        for (auto iter = dq1.begin(); iter != dq1.end(); ++iter, ++i) {
            if (*iter != i) {
                error_msg("DequeTestCase2 stage 3");
            }
        }
    }
}  // namespace mySTL