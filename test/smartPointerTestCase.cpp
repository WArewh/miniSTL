#include "smartPointerTestCase.h"

#include "smartPointer.h"

namespace mySTL {
    void SmartPointerTestCase::testAll() {
        printf("\nSmartPointerTestCase start!\n");
        testCase1();
        testCase2();
        testCase3();
        printf("SmartPointerTestCase pass!\n");
    }
    void SmartPointerTestCase::testCase1() {
        unique_ptr<int> up1(new int(10));
        if (*up1.get() != *up1) {
            error_msg("SmartPointerTestCase::testCase1 stage 1");
        }
        auto ptr1 = new int(8);
        up1.reset(ptr1);
        auto temp = *ptr1;
        up1.reset();
        if (temp != 8 || up1.get() != nullptr) {
            error_msg("SmartPointerTestCase::testCase1 stage 2");
        }
        up1.reset(ptr1);
        auto ptr2 = up1.release();
        if (ptr2 != ptr1 || up1.get() != nullptr) {
            error_msg("SmartPointerTestCase::testCase1 stage 3");
        }
    }

    void SmartPointerTestCase::testCase2() {
        shared_ptr<int> sp1(new int(10));
        if (*sp1.get() != *sp1) {
            error_msg("SmartPointerTestCase::testCase2 stage 1");
        }
        shared_ptr<int> sp2(sp1);
        if (sp2.get() != sp1.get() || sp2.use_count() != 2) {
            error_msg("SmartPointerTestCase::testCase2 stage 2");
        }
        shared_ptr<int> sp3;
        sp3 = sp2;
        sp3 = sp3;
        if (sp3.get() != sp2.get() || sp2.use_count() != 3) {
            error_msg("SmartPointerTestCase::testCase2 stage 3");
        }
    }

    void SmartPointerTestCase::testCase3() {
        weak_ptr<int> wp1(new int(10));
        if (*wp1.get() != *wp1) {
            error_msg("SmartPointerTestCase::testCase3 stage 1");
        }
        weak_ptr<int> wp2(wp1);
        if (wp2.get() != wp1.get() || wp2.use_count() != 0) {
            error_msg("SmartPointerTestCase::testCase3 stage 2");
        }
        weak_ptr<int> wp3 = wp2;
        wp3 = wp3;
        if (wp3.get() != wp2.get() || wp2.use_count() != 0) {
            error_msg("SmartPointerTestCase::testCase3 stage 3");
        }
    }

    void SmartPointerTestCase::testCase4() {
        int*            iptr = new int(10);
        shared_ptr<int> sp1(iptr);
        weak_ptr<int>   wp1(sp1);
        if (sp1.get() != wp1.get() || sp1.use_count() != 1) {
            error_msg("SmartPointerTestCase::testCase4 stage 1");
        }
        shared_ptr<int> sp2(new int(5));
        sp1 = sp2;
        if (wp1.get() != nullptr) {
            error_msg("SmartPointerTestCase::testCase4 stage 2");
        }
        wp1.lock();
        if (wp1.get() != iptr) {
            error_msg("SmartPointerTestCase::testCase4 stage 3");
        }
    }
}  // namespace mySTL