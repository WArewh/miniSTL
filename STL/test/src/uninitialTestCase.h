#ifndef _MYSTL_UNINITIALTESTCASE_H
#define _MYSTL_UNINITIALTESTCASE_H

#include "test.h"

namespace mySTL
{
    class UninitialTestCase : public TestCase
    {
        void testAll() override;
        void testUninitCopy();
        void testUninitFill();
    };
}  // namespace mySTL

#endif