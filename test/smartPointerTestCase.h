#ifndef _MYSTL_SMARTPOINTERTESTCASE_H
#define _MYSTL_SMARTPOINTERTESTCASE_H

#include "test.h"

namespace mySTL {
    class SmartPointerTestCase : public TestCase {
        void testAll() override;
        void testCase1();  // unique_ptr
        void testCase2();  // shared_ptr
        void testCase3();  // weak_ptr
        void testCase4();  // shared_ptr和weak_ptr
    };
}  // namespace mySTL

#endif
