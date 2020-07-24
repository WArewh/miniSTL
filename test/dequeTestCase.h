#ifndef _MYSTL_DEQUETESTCASE_H
#define _MYSTL_DEQUETESTCASE_H

#include "test.h"

namespace mySTL {
    class DequeTestCase : public TestCase {
        void testAll() override;
        void testCase1();  //测试初始化和重载符号
        void testCase2();  //测试push和pop
    };
}  // namespace mySTL

#endif
