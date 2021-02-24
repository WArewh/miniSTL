#include "uninitialTestCase.h"

#include "../tinySTL/uninitial.h"

namespace mySTL
{
    void UninitialTestCase::testAll()
    {
        printf("\nuninitialTestCase start!\n");
        testUninitCopy();
        testUninitFill();
        printf("uninitialTestCase pass!\n");
    }
    void UninitialTestCase::testUninitCopy()
    {
        //原生指针
        const int size = 10;

        int arr[10] = {1, 2, 3, 4, 5, 5, 4, 3, 2, 1};
        int* res = new int[size];

        uninitialized_copy(arr, arr + size, res);

        for (int i = 0; i < size; ++i)
        {
            if (res[i] != arr[i])
            {
                delete[] res;
                error_msg("uninitialTestCase::testUninitCopy");
            }
        }
        delete[] res;
    }
    void UninitialTestCase::testUninitFill()
    {
        //原生指针
        const int size = 10;

        int arr[10] = {5, 5, 5, 5, 5, 4, 4, 4, 4, 4};
        int* res = new int[size];

        auto iter = uninitialized_fill_n(res, 5, 5);
        uninitialized_fill(iter, res + size, 4);

        for (int i = 0; i < size; ++i)
        {
            if (res[i] != arr[i])
            {
                delete[] res;
                error_msg("uninitialTestCase::testUninitCopy");
            }
        }
        delete[] res;
    }
}  // namespace mySTL