#include <iostream>

#include "algorithmTestCase.h"
#include "allocatorTestCase.h"
#include "listTestCase.h"
#include "smartPointerTestCase.h"
#include "test.h"
#include "uninitialTestCase.h"
#include "vectorTestCase.h"
using namespace mySTL;

int main() {
    Test test;

    allocatorTestCase    alloc_case;
    AlgorithmTestCase    algo_case;
    UninitialTestCase    uninit_case;
    SmartPointerTestCase pointer_case;
    VectorTestCase       vec_case;
    ListTestCase         list_case;

    test.addcase(&alloc_case);
    test.addcase(&algo_case);
    test.addcase(&uninit_case);
    test.addcase(&pointer_case);
    test.addcase(&vec_case);
    test.addcase(&list_case);

    test.run();
    return 0;
}