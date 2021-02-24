#include "allocatorTestCase.h"

#include <unistd.h>

#include "../tinySTL/allocator.h"

namespace mySTL
{

    void allocatorTestCase::testAll()
    {
        printf("\nallocatorTestCase start!\n");
        testCase1();
        testCase2();
        printf("allocatorTestCase pass!\n");
    }

    void allocatorTestCase::testCase1()
    {
        using allocator = Allocator<int>;
        int* ptr[50];
        for (int i = 0; i < 50; ++i)
        {
            for (int j = 0; j < 50; ++j)
            {
                ptr[j] = allocator::allocate(i);
            }
            for (int j = 0; j < 50; ++j)
            {
                allocator::deallocate(ptr[j], i);
            }
        }
    }

    void allocatorTestCase::testCase2()
    {
        using allocator = Allocator<int*>;
        for (int i = 0; i < 20; ++i)
        {
            auto ptr = allocator::allocate(i);
            allocator::deallocate(ptr, i);
        }
    }
}  // namespace mySTL