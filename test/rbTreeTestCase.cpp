#include "rbTreeTestCase.h"

#include "rbTree.h"

namespace mySTL {
    void RBTreeTestCase::testAll() {
        printf("\nRBTreeTestCase start!\n");
        testCase1();
        // testCase2();
        // testCase3();
        printf("RBTreeTestCase pass!\n");
    }
    void RBTreeTestCase::testCase1() {
        RBTree<int> tree;
        for (int i = 1; i <= 10; ++i) {
            tree.insert(i);
        }
        for (int i = 20; i > 10; --i) {
            tree.insert(i);
        }

        if (*tree.begin() != 1 || *tree.end() != 20 || tree.size() != 20) {
            error_msg("RBTreeTestCase1 stage 1");
        }
        int i = 1;
        for (auto iter = tree.begin(); iter != tree.end(); ++iter, ++i) {
            if (*iter != i) {
                error_msg("RBTreeTestCase1 stage 2");
            }
        }
        for (auto iter = tree.end(); iter != tree.begin(); --iter, --i) {
            if (*iter != i) {
                error_msg("RBTreeTestCase1 stage 3");
            }
        }
    }
}  // namespace mySTL