#ifndef _MYSTL_TUPLETESTCASE_H
#define _MYSTL_TUPLETESTCASE_H

#include "test.h"

namespace mySTL
{
    class tupleTestCase : public TestCase
    {
        void testAll() override;
        void testCase1();
        void testCase2();
        // void testCase3();
    };
}  // namespace mySTL

#endif