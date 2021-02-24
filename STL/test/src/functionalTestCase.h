#ifndef TEST_FUNCTIONALTESTCASE_H_
#define TEST_FUNCTIONALTESTCASE_H_

#include "test.h"

namespace mySTL
{
    class functionalTestCase : public TestCase
    {
    public:
        void testAll();
        void testCase1();
        void testCase2();
        void testCase3();
    };
}  // namespace mySTL
#endif