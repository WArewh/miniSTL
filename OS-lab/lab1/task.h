#ifndef LAB1_TASK_H
#define LAB1_TASK_H

#include <string>

struct Task {
    std::string m_name;  //名字
    int m_arrival;       //到达时间
    int m_require;       //需要的时间
    int m_priority;      //优先级
    int m_already;       //已经执行时间
    int m_finish;        //完成时间

    Task() : m_already(0) {}
};

#endif