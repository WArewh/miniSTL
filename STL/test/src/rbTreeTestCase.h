#ifndef MYSTL_RBTREETESTCASE_H
#define MYSTL_RBTREETESTCASE_H

#include "test.h"

namespace mySTL
{
    class RBTreeTestCase : public TestCase
    {
        void testAll() override;
        void testCase1();
        void testCase2();
        void testCase3();
    };
}  // namespace mySTL

#endif