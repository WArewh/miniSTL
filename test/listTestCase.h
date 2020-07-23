#ifndef _MYSTL_LISTTESTCASE_H
#define _MYSTL_LISTTESTCASE_H

#include "test.h"

namespace mySTL {
    class ListTestCase : public TestCase {
        void testAll() override;
        void testCase1();  //测试初始化和重载符号
        void testCase2();  //测试删除和删除
        void testCase3();  //测试翻转和
    };
}  // namespace mySTL

#endif