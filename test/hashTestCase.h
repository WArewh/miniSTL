#ifndef MYSTL_HASHTESTCASE_H
#define MYSTL_HASHTESTCASE_H

#include "test.h"

namespace mySTL {
    class HashTestCase : public TestCase {
        void testAll() override;
        void testCase1();
        void testCase2();
        void testCase3();
    };
}  // namespace mySTL

#endif