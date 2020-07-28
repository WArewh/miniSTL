#include "heapTestCase.h"

#include "algorithm.h"
#include "vector.h"

namespace mySTL {
    void HeapTestCase::testAll() {
        printf("\nHeapTestCase start!\n");
        testCase1();
        // testCase2();
        printf("HeapTestCase pass!\n");
    }

    void HeapTestCase::testCase1() {
        vector<int> vec;
        for (int i = 0; i < 10; ++i) {
            vec.push_back(i);
        }
        make_heap(vec + 0, vec + 10);
        for (int i = 0; i < 4; ++i) {
            int left = i * 2 + 1;
            int right = i * 2 + 2;
            if (vec[i] < vec[left] || vec[i] < vec[right]) {
                error_msg("HeapTestCase1 stage 1");
            }
        }
        sort_heap(vec + 0, vec + 10);
        for (int i = 0; i < 10; ++i) {
            if (vec[i] != i) {
                error_msg("HeapTestCase1 stage 2");
            }
        }
    }

}  // namespace mySTL