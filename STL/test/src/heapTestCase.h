#ifndef _MYSTL_HEAPTESTCASE_H
#define _MYSTL_HEAPTESTCASE_H

#include "test.h"

namespace mySTL
{
    class HeapTestCase : public TestCase
    {
        void testAll() override;
        void testCase1();
        void testCase2();
        void testCase3();
    };
}  // namespace mySTL

#endif
