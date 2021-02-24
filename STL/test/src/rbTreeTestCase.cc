#include "rbTreeTestCase.h"

#include "../tinySTL/map.h"
#include "../tinySTL/rbTree.h"
#include "../tinySTL/set.h"

namespace mySTL
{
    void RBTreeTestCase::testAll()
    {
        printf("\nRBTreeTestCase start!\n");
        testCase1();
        testCase2();
        testCase3();
        printf("RBTreeTestCase pass!\n");
    }
    void RBTreeTestCase::testCase1()
    {
        RBTree<int, int> tree;
        tree.clear();
        for (int i = 1; i <= 10; ++i)
        {
            tree.insert(i);
        }
        for (int i = 20; i > 10; --i)
        {
            tree.insert(i);
        }

        if (*tree.begin() != 1 || *tree.end() != 20 || tree.size() != 20)
        {
            error_msg("RBTreeTestCase1 stage 1");
        }
        int i = 1;
        for (auto iter = tree.begin(); iter != tree.end(); ++iter, ++i)
        {
            if (*iter != i)
            {
                error_msg("RBTreeTestCase1 stage 2");
            }
        }
        for (auto iter = tree.end(); iter != tree.begin(); --iter, --i)
        {
            if (*iter != i)
            {
                error_msg("RBTreeTestCase1 stage 3");
            }
        }
        tree.clear();
        for (int i = 0; i < 10; ++i)
        {
            for (int j = 0; j < 10; ++j)
            {
                tree.insert_unique(i);
            }
        }
        i = 0;
        if (tree.size() != 10)
        {
            error_msg("RBTreeTestCase1 stage 4");
        }
        for (auto iter = tree.begin(); iter != tree.end(); ++iter, ++i)
        {
            if (*iter != i)
            {
                error_msg("RBTreeTestCase1 stage 5");
            }
        }
    }
    void RBTreeTestCase::testCase2()
    {
        set<int> s;
        for (int i = 1; i <= 10; ++i)
        {
            s.insert(i);
        }
        for (int i = 20; i > 10; --i)
        {
            s.insert(i);
        }

        if (*s.begin() != 1 || *s.end() != 20 || s.size() != 20)
        {
            error_msg("RBTreeTestCase2 stage 1");
        }
        int i = 1;
        for (auto iter = s.begin(); iter != s.end(); ++iter, ++i)
        {
            if (*iter != i)
            {
                error_msg("RBTreeTestCase2 stage 2");
            }
        }
        for (auto iter = s.end(); iter != s.begin(); --iter, --i)
        {
            if (*iter != i)
            {
                error_msg("RBTreeTestCase2 stage 3");
            }
        }
    }
    void RBTreeTestCase::testCase3()
    {
        map<char, int> mp;
        for (int i = 0; i < 26; ++i)
        {
            mp.insert(pair<char, int>('a' + i, i));
        }
        for (int i = 0; i < 26; ++i)
        {
            if (mp['a' + i] != i)
            {
                error_msg("RBTreeTestCase3 stage 1");
            }
        }
        mp.clear();
        mp['a'] = 10;
        mp['b'] = 15;
        mp['c'] = 20;
        if (mp.size() != 3)
        {
            error_msg("RBTreeTestCase3 stage 2");
        }
        int i = 10;
        for (auto iter = mp.begin(); iter != mp.end(); ++iter, i += 5)
        {
            if (iter->second != i)
            {
                error_msg("RBTreeTestCase3 stage 2");
            }
        }
    }
}  // namespace mySTL