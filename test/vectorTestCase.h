#ifndef _MYSTL_VECTORTESTCASE_H
#define _MYSTL_VECTORTESTCASE_H

#include "test.h"

namespace mySTL {
    class VectorTestCase : public TestCase {
        void testAll() override;
        void testCase1();  //测试初始化和重载符号
        void testCase2();  //测试容量改变
        void testCase3();  //测试插入和删除
    };
}  // namespace mySTL


#endif