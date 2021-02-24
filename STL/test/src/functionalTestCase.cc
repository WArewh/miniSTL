#include "functionalTestCase.h"

#include "../tinySTL/functional.h"

namespace mySTL
{
    void functionalTestCase::testAll()
    {
        printf("\nfunctionalTestCase start!\n");
        testCase1();
        testCase2();
        printf("functionalTestCase pass!\n");
    }
    void functionalTestCase::testCase1()
    {
        auto func1 = plus<int>();
        func1(10, 20);
        if (func1(10, 20) != 30)
        {
            error_msg("functionalTestCase::testCase1");
        }
    }

    int testfunction(int a, int b) { return a + b; };

    void functionalTestCase::testCase2()
    {
        auto func1 = testfunction;

        function<int(int, int)> func2(func1);
        if (func2(10, 20) != 30)
        {
            error_msg("functionalTestCase::testCase2");
        }
    }

    void functionalTestCase::testCase3() {}
}  // namespace mySTL