#include "display.h"

void printTasks(const std::vector<Task> tasks) {
    printf("***********************************\n");
    printf("任务 到达时间 需要时间 优先级\n");
    for (const auto& task : tasks) {
        printf("%-5s%-9d%-9d%-7d\n", task.m_name.c_str(), task.m_arrival, task.m_require,
               task.m_priority);
    }
    printf("*************************************\n");
}

void printSchedule(const int time, const Task& task) {
    printf("%d:%s\n", time, task.m_name.c_str());
}
