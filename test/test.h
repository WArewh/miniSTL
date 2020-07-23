#ifndef _MYSTL_TEST_H
#define _MYSTL_TEST_H

#include <cstdio>
#include <vector>

namespace mySTL {
    //抽象基类
    class TestCase {
    public:
        virtual ~TestCase() {}
        virtual void testAll() = 0;
    };

    class Test {
    public:
        void run();
        void addcase(TestCase* test_case) { case_vector.push_back(test_case); }

    private:
        std::vector<TestCase*> case_vector;
    };

    void error_msg(const char* const msg);

}  // namespace mySTL
#endif