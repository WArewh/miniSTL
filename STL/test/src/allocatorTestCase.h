#ifndef _MYSTL_ALLOCATORTESTCASE_H
#define _MYSTL_ALLOCATORTESTCASE_H

#include "test.h"

namespace mySTL
{
    class allocatorTestCase : public TestCase
    {
        void testAll() override;
        void testCase1();
        void testCase2();
    };
}  // namespace mySTL

#endif