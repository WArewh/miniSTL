#ifndef _MYSTL_ALGORITHMTESTCASE_H
#define _MYSTL_ALGORITHMTESTCASE_H

#include "test.h"

namespace mySTL
{
    class AlgorithmTestCase : public TestCase
    {
    public:
        void testAll() override;
        void testCase1();  // Fill
        void testCase2();  // Copy
        void testCase3();  // min max swap
    };
}  // namespace mySTL

#endif