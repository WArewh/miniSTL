#include "vectorTestCase.h"

#include "vector.h"

namespace mySTL {
    void VectorTestCase::testAll() {
        printf("\nVectorTestCase start!\n");
        testCase1();
        testCase2();
        testCase3();
        printf("VectorTestCase pass!\n");
    }
    void VectorTestCase::testCase1() {
        mySTL::vector<int> v1(5, 2);
        mySTL::vector<int> v2(5);
        for (int i = 0; i < 5; ++i) {
            v2[i] = 2;
        }
        if (v2 != v1) {
            error_msg("VectorTestCase::testCase1 stage 1");
        }
        while (!v1.empty()) {
            v1.pop_back();
        }
        if (v1.size() != 0) {
            error_msg("VectorTestCase::testCase1 stage 2");
        }
        auto elem = v2 + 3;
        *elem = 5;
        if (v2[3] != 5) {
            error_msg("VectorTestCase::testCase1 stage 3");
        }
    }
    void VectorTestCase::testCase2() {
        mySTL::vector<int> vec;
        // resize
        vec.resize(5, 1);
        if (vec.size() != vec.capacity()) {
            error_msg("VectorTestCase::testCase2 stage 1");
        }
        vec.resize(6, 6);
        if (vec.size() != 6 || vec.capacity() != 10) {
            error_msg("VectorTestCase::testCase2 stage 2");
        }
        // // reserve
        vec.reserve(20);
        if (vec.size() != 6 || vec.capacity() != 20) {
            error_msg("VectorTestCase::testCase2 stage 3");
        }
        // // clear
        vec.clear();
        if (vec.size() != 0 || vec.capacity() != 20) {
            error_msg("VectorTestCase::testCase2 stage 4");
        }
        vec.resize(5);
        vec.shrink_to_fit();
        if (vec.size() != 5 || vec.capacity() != 5) {
            error_msg("VectorTestCase::testCase2 stage 5");
        }
    }
    void VectorTestCase::testCase3() {
        mySTL::vector<int> v1(3, 3);
        mySTL::vector<int> v2;
        v1.push_back(3);
        v1.insert(v1 + 1, 5, 4);
        v2.push_back(3);
        v2.insert(v2.end(), 3, 3);
        v2.insert(v2 + 1, 5, 4);
        if (v1 != v2) {
            error_msg("VectorTestCase::testCase3 stage 1");
        }
    }
}  // namespace mySTL