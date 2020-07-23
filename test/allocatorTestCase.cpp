#include "allocatorTestCase.h"

#include <unistd.h>

#include "allocator.h"

namespace mySTL {

    void allocatorTestCase::testAll() {
        printf("\nallocatorTestCase start!\n");
        testCase1();
        printf("allocatorTestCase pass!\n");
    }

    void allocatorTestCase::testCase1() {
        int cnt = 10000000;

        Allocator<int> alloc;
        for (int i = 0; i < cnt; ++i) {
            auto ptr = alloc.allocate();
            alloc.construct(ptr, 10);
            alloc.destroy(ptr);
            alloc.deallocate(ptr);
        }
    }
}  // namespace mySTL