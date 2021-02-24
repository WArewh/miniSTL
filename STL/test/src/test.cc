#include "test.h"

#include <cstdio>
#include <cstdlib>
namespace mySTL
{

    void Test::run()
    {
        printf("*********************************\n");
        printf("Test Begin!\n");
        for (auto ptr : case_vector)
        {
            ptr->testAll();
        }
        printf("\nTest Finish!\n");
        printf("*********************************\n");
    }

    void error_msg(const char* const msg)
    {
        fprintf(stderr, "Error in:%s\n\n", msg);
        exit(1);
    }
}  // namespace mySTL