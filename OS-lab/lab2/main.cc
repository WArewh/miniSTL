#include <stdio.h>
#include <stdlib.h>

#include <string>

#include "schedule.h"

std::vector<Page> page_vec;


#define TestFile(num)                      \
    fp = fopen((str + #num).c_str(), "r"); \
    if (!fp) {                             \
        perror("fopen");                   \
        exit(1);                           \
    }                                      \
    InputTasks(fp);                        \
    Schedule();                            \
    page_vec.clear();                      \
    fclose(fp);

void InputTasks(FILE* fp) {
    int n;
    fscanf(fp, "%d", &n);
    for (int i = 0; i < n; ++i) {
        int no;
        fscanf(fp, "%d", &no);
        page_vec.push_back(Page(no));
    }
}

void Schedule() {

    FIFO fifo(page_vec);
    OPT opt(page_vec);
    LRU lru(page_vec);

    std::vector<AbstractSchedule*> sched_vec = {&fifo, &lru, &opt};

    for (auto& sched : sched_vec) {
        printf("%s结果:\n", sched->name());
        sched->run();
        sched->calAndPrintPerformance();
    }
}

int main() {
    std::string str = "test/test";
    FILE* fp;
    TestFile(1);
    // TestFile(2);
    return 0;
}