#include "tupleTestCase.h"

#include "../tinySTL/tuple.h"

namespace mySTL
{
    void tupleTestCase::testAll()
    {
        printf("\ntupleTestCase start!\n");
        testCase1();
        testCase2();
        printf("tupleTestCase pass!\n");
    }

    void tupleTestCase::testCase1()
    {
        tuple<int, int, int> t1(1, 2, 3);
        if (tuple_get<0>(t1) != 1 || tuple_get<1>(t1) != 2 || tuple_get<2>(t1) != 3)
        {
            error_msg("tupleTestCase::testCase1 stage1");
        }

        tuple<int, long, double, float> t2(1, 2, 3.0, 4.0);

        if (tuple_get<0>(t2) != 1 || tuple_get<1>(t2) != 2 || tuple_get<2>(t2) != 3.0
            || tuple_get<3>(t2) != 4.0)
        {
            error_msg("tupleTestCase::testCase1 stage2");
        }
    }

    void tupleTestCase::testCase2()
    {
        int a = 1;
        long b = 2;
        char c = 'c';
        float f = 4.5;
        double d = 5.5;
        tuple<int, long, char, float, double> t1(a, b, c, f, d);
        if (tuple_get<0>(t1) != a || tuple_get<1>(t1) != b || tuple_get<2>(t1) != c
            || tuple_get<3>(t1) != f || tuple_get<4>(t1) != d)
        {
            error_msg("tupleTestCase::testCase1");
        }
    }

}  // namespace mySTL