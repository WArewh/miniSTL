#include <iostream>

#include "algorithmTestCase.h"
#include "allocatorTestCase.h"
#include "basicStringTestCase.h"
#include "dequeTestCase.h"
#include "functionalTestCase.h"
#include "heapTestCase.h"
#include "listTestCase.h"
#include "rbTreeTestCase.h"
#include "smartPointerTestCase.h"
#include "test.h"
#include "tupleTestCase.h"
#include "typeTraitTestCase.h"
#include "uninitialTestCase.h"
#include "vectorTestCase.h"
using namespace mySTL;

int main()
{
    Test test;

    typeTraitTestCase type_case;
    allocatorTestCase alloc_case;
    AlgorithmTestCase algo_case;
    UninitialTestCase uninit_case;
    SmartPointerTestCase pointer_case;
    functionalTestCase func_case;
    VectorTestCase vec_case;
    ListTestCase list_case;
    DequeTestCase deq_case;
    HeapTestCase heap_case;
    RBTreeTestCase rb_case;
    tupleTestCase tuple_case;
    BasicStringTestCase string_case;


    test.addcase(&type_case);
    test.addcase(&alloc_case);
    test.addcase(&algo_case);
    test.addcase(&uninit_case);
    test.addcase(&pointer_case);
    test.addcase(&func_case);
    test.addcase(&vec_case);
    test.addcase(&list_case);
    test.addcase(&deq_case);
    test.addcase(&heap_case);
    test.addcase(&rb_case);
    test.addcase(&tuple_case);
    test.addcase(&string_case);

    test.run();
    return 0;
}