#ifndef _MYSTL_ALLOCATORTESTCASE_H
#define _MYSTL_ALLOCATORTESTCASE_H

#include "test.h"

namespace mySTL {
    class allocatorTestCase : public TestCase {
        void testAll() override;
        void testCase1();  //内存泄露
    };
}  // namespace mySTL

#endif