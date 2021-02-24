#include "listTestCase.h"

#include "../tinySTL/list.h"

namespace mySTL
{
    void ListTestCase::testAll()
    {
        printf("\nListTestCase start!\n");
        testCase1();
        testCase2();
        testCase3();
        printf("ListTestCase pass!\n");
    }
    void ListTestCase::testCase1()
    {
        list<int> list_1;
        if (!list_1.empty())
        {
            error_msg("ListTestCase1 stage 1");
        }
        list<int> list_2(3, 5);
        list<int> list_3(list_2);
        if (list_2 != list_3 || list_2.size() != 3)
        {
            error_msg("ListTestCase1 stage 2");
        }
        list_2.clear();
        if (!list_2.empty())
        {
            error_msg("ListTestCase1 stage 3");
        }
    }
    void ListTestCase::testCase2()
    {
        list<int> list_1;
        list<int> list_2;
        for (size_t i = 0; i < 5; ++i)
        {
            list_1.push_back(1);
            list_2.push_back(1);
        }
        for (size_t i = 0; i < 5; ++i)
        {
            list_1.push_front(2);
            list_2.push_front(2);
        }
        if (list_1 != list_2)
        {
            error_msg("ListTestCase2 stage 1");
        }
        list_1.push_front(5);
        list_1.push_back(5);
        list_1.pop_back();
        list_1.pop_front();
        if (list_1 != list_2 || list_1.size() != 10)
        {
            error_msg("ListTestCase2 stage 2");
        }
        list_1.remove(2);
        list_2.pop_front();
        list_2.remove(2);
        list_2.pop_back();
        if (list_1.size() != 5 || list_2.size() != 4)
        {
            error_msg("ListTestCase2 stage 3");
        }
    }
    void ListTestCase::testCase3()
    {
        list<int> list_1(5, 1);
        list<int> list_2(5, 2);
        list_1.splice(list_1.begin(), list_2);
        if (list_1.size() != 10)
        {
            error_msg("ListTestCase3 stage 1");
        }
        list<int> list_3(5, 1);
        list<int> list_4(5, 2);
        for (size_t i = 0; i < 5; ++i)
        {
            list_3.push_front(2);
            list_4.push_front(1);
        }
        // list_3.reverse();
        // if (list_3 != list_4) {
        //     error_msg("ListTestCase3 stage 2");
        // }
    }
}  // namespace mySTL