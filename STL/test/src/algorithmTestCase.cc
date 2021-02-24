#include "algorithmTestCase.h"

#include "../tinySTL/algorithm.h"

namespace mySTL
{

    void AlgorithmTestCase::testAll()
    {
        printf("\nAlgorithmTestCase start!\n");
        testCase1();
        printf("AlgorithmTestCase pass!\n");
    }

    void AlgorithmTestCase::testCase1()
    {
        const int size = 8;
        int* arr = new int[size];
        int res[size] = {50, 50, 50, 50, 60, 60, 60, 60};
        auto iter = fill_n(arr, 4, 50);
        fill(iter, iter + 4, 60);

        for (int i = 0; i < size; ++i)
        {
            if (res[i] != arr[i])
            {
                delete[] arr;
                error_msg("AlgorithmTestCase::testFill");
            }
        }
        delete[] arr;
    }
}  // namespace mySTL