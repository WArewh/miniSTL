#ifndef _MYSTL_BASICSTRINGTESTCASE_H
#define _MYSTL_BASICSTRINGTESTCASE_H

#include "test.h"

namespace mySTL
{
    class BasicStringTestCase : public TestCase
    {
        void testAll() override;
        void testCase1();
        void testCase2();
        void testCase3();
        void testCase4();
    };
}  // namespace mySTL

#endif