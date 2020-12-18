#include <stdio.h>
#include <stdlib.h>

#include "display.h"
#include "schedule.h"

#define TestFile(num)                      \
    fp = fopen((str + #num).c_str(), "r"); \
    if (!fp) {                             \
        perror("fopen");                   \
        exit(1);                           \
    }                                      \
    InputTasks(fp);                        \
    Schedule();                            \
    tasks.clear();                         \
    fclose(fp);

std::vector<Task> tasks;

void InputTasks(FILE* fp) {
    int n;
    fscanf(fp, "%d", &n);
    for (int i = 0; i < n; ++i) {
        Task t;
        char buf[10];
        fscanf(fp, "%s %d %d %d", buf, &t.m_arrival, &t.m_require, &t.m_priority);
        t.m_name = buf;
        tasks.push_back(t);
    }
    printTasks(tasks);
}

void Schedule() {
    FIFO fifo(tasks);
    SJF sjf(tasks);
    PP pp(tasks);
    RR rr(tasks);
    MultiFeedback mf(tasks);

    std::vector<AbstractSchedule*> sched_vec = {&fifo, &sjf, &pp, &rr, &mf};
    for (auto& sched : sched_vec) {
        printf("%s结果:\n", sched->name());
        sched->run();
        printf("\n");
        sched->calAndPrintPerformance();
        printf("\n");
    }
}

int main() {
    std::string str = "test/test";
    FILE* fp;
    // TestFile(1);
    // TestFile(2);
    TestFile(3);
    return 0;
}