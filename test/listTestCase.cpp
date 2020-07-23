#include "listTestCase.h"

#include "list.h"

namespace mySTL {
    void ListTestCase::testAll() {
        printf("\nListTestCase start!\n");
        testCase1();
        testCase2();
        testCase3();
        printf("ListTestCase pass!\n");
    }
    void ListTestCase::testCase1() {
        list<int> list_1;
        if (!list_1.empty()) {
            error_msg("ListTestCase1 stage 1");
        }
        list<int> list_2(3, 5);
        list<int> list_3(list_2);
        if (list_2 != list_3) {
            error_msg("ListTestCase1 stage 2");
        }
        list_2.clear();
        if (!list_2.empty()) {
            error_msg("ListTestCase1 stage 3");
        }
    }
    void ListTestCase::testCase2() {}
    void ListTestCase::testCase3() {}
}  // namespace mySTL