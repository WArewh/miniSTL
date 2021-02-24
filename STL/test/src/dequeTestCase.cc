#include "dequeTestCase.h"

#include "../tinySTL/deque.h"
#include "../tinySTL/list.h"
#include "../tinySTL/queue.h"
#include "../tinySTL/stack.h"

namespace mySTL
{
    void DequeTestCase::testAll()
    {
        printf("\nDequeTestCase start!\n");
        testCase1();
        testCase2();
        testCase3();
        testCase4();
        printf("DequeTestCase pass!\n");
    }

    void DequeTestCase::testCase1()
    {
        deque<int, Allocator<int>, 4> dq1(10, 2);
        deque<int> dq2;
        deque<int> dq3(2, 2);
        if (dq1.size() != 10 || dq2.size() != 0 || dq3.size() != 2)
        {
            error_msg("DequeTestCase1 stage 1");
        }
        for (auto iter = dq1.begin(); iter != dq1.end(); ++iter)
        {
            if (*iter != 2)
            {
                error_msg("DequeTestCase1 stage 2");
            }
        }
        dq1.clear();
        if (dq1.size() != 0)
        {
            error_msg("DequeTestCase1 stage 3");
        }
    }
    void DequeTestCase::testCase2()
    {
        deque<int, Allocator<int>, 4> dq1;
        deque<int, Allocator<int>, 4> dq2;
        for (int i = 0; i < 5; ++i)
        {
            dq1.push_back(i);
            dq2.push_back(i);
        }
        for (int i = 5; i < 20; ++i)
        {
            dq1.push_back(i);
            dq2.push_front(i);
        }
        int i = 0;
        for (auto iter = dq1.begin(); iter != dq1.end(); ++iter, ++i)
        {
            if (*iter != i)
            {
                error_msg("DequeTestCase2 stage 1");
            }
        }
        dq1.clear();
        if (dq1.size() != 0 || dq2.back() != 4 || dq2.front() != 19)
        {
            error_msg("DequeTestCase2 stage 2");
        }
        for (int i = 20; i < 40; ++i)
        {
            dq1.push_back(i);
        }
        for (int i = 19; i >= 0; --i)
        {
            dq1.push_front(i);
        }
        i = 0;
        for (auto iter = dq1.begin(); iter != dq1.end(); ++iter, ++i)
        {
            if (*iter != i)
            {
                error_msg("DequeTestCase2 stage 3");
            }
        }
        for (int i = 0; i < 20; ++i)
        {
            dq1.pop_back();
            dq1.pop_front();
        }
        if (dq1.size() != 0)
        {
            error_msg("DequeTestCase2 stage 2");
        }
    }

    void DequeTestCase::testCase3()
    {
        queue<int> q1;
        queue<int, list<int>> q2;
        for (int i = 10; i < 20; ++i)
        {
            q1.push(i);
            q2.push(i);
        }
        if ((q1.front() != 10 || q1.back() != 19 || q1.size() != 10)
            || (q2.front() != 10 || q2.back() != 19 || q2.size() != 10))
        {
            error_msg("DequeTestCase3 stage 1");
        }
        for (int i = 0; i < 5; ++i)
        {
            q1.pop();
            q2.pop();
        }
        if ((q1.front() != 15 || q1.back() != 19 || q1.size() != 5)
            || (q2.front() != 15 || q2.back() != 19 || q2.size() != 5))
        {
            error_msg("DequeTestCase3 stage 2");
        }
    }
    void DequeTestCase::testCase4()
    {
        stack<int> st1;
        stack<int, list<int>> st2;
        for (int i = 10; i < 20; ++i)
        {
            st1.push(i);
            st2.push(i);
        }
        if ((st1.top() != 19 || st1.size() != 10) || (st2.top() != 19 || st2.size() != 10))
        {
            error_msg("DequeTestCase4 stage 1");
        }
        for (int i = 0; i < 5; ++i)
        {
            st1.pop();
            st2.pop();
        }
        if ((st1.top() != 14 || st1.size() != 5) || (st2.top() != 14 || st2.size() != 5))
        {
            error_msg("DequeTestCase4 stage 2");
        }
    }
}  // namespace mySTL