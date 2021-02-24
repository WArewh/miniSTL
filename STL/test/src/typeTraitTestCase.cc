#include "typeTraitTestCase.h"

#include "../tinySTL/typeTraits.h"

namespace mySTL
{
    void typeTraitTestCase::testAll()
    {
        printf("\ntypeTraitTestCase start!\n");
        testCase1();
        testCase2();
        testCase3();
        printf("typeTraitTestCase pass!\n");
    }
    void typeTraitTestCase::testCase1()
    {
        if (!is_same<int, int>())
        {
            error_msg("typeTraitTestCase::testCase1 stage1");
        }
        if (is_same<int, const int>())
        {
            error_msg("typeTraitTestCase::testCase1 stage2");
        }
        if (!is_same<int, remove_cv_t<const int>>())
        {
            error_msg("typeTraitTestCase::testCase1 stage3");
        }
        if (!is_same<int&&, add_rv_ref_t<int>>())
        {
            error_msg("typeTraitTestCase::testCase1 stage3");
        }
    }
    void typeTraitTestCase::testCase2() {}
    void typeTraitTestCase::testCase3() {}
}  // namespace mySTL