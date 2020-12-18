#ifndef LAB1_SCHEDULE_H
#define LAB1_SCHEDULE_H

#include <queue>
#include <vector>

#include "task.h"
struct FIFO_compare {
    bool operator()(const Task& t1, const Task& t2);
};

class AbstractSchedule {

public:
    AbstractSchedule() = default;
    AbstractSchedule(const std::vector<Task>& tasks);
    virtual void run() = 0;
    virtual const char* name() = 0;
    void setCurrentTime(int time) { current_time = time; }
    void calAndPrintPerformance();
    std::vector<Task>& getCalVec() { return cal_vec; }

protected:
    //将任务按照到达时间排序
    std::priority_queue<Task, std::vector<Task>, FIFO_compare> m_task_queue;
    //计算性能指标容器
    std::vector<Task> cal_vec;
    //当前时间
    int current_time;
};

//　先来先服务
class FIFO : public AbstractSchedule {
public:
    FIFO() = default;
    FIFO(const std::vector<Task>& tasks);
    const char* name() { return "先来先服务"; }
    void run();

private:
    std::priority_queue<Task, std::vector<Task>, FIFO_compare> current_task_queue;
};

// 短作业优先
struct SJF_compare {
    bool operator()(const Task& t1, const Task& t2);
};

class SJF : public AbstractSchedule {
public:
    SJF() = default;
    SJF(const std::vector<Task>& tasks);
    const char* name() { return "短作业调度"; }
    void run();

private:
    std::priority_queue<Task, std::vector<Task>, SJF_compare> current_task_queue;
};

//优先级调度
struct PP_compare {
    bool operator()(const Task& t1, const Task& t2);
};

class PP : public AbstractSchedule {
public:
    PP() = default;
    PP(const std::vector<Task>& tasks);
    const char* name() { return "优先级调度"; }
    void run();

private:
    std::priority_queue<Task, std::vector<Task>, PP_compare> current_task_queue;
};

//轮转调度
class RR : public AbstractSchedule {
public:
    RR() = default;
    RR(int slice, const std::vector<Task>& tasks);
    RR(const std::vector<Task>& tasks);
    const char* name() { return "轮转法调度"; }
    void run();
    void setSlice(int slice) { m_slice = slice; }
    std::queue<Task>& getQueue() { return current_task_queue; }

public:
    int m_slice;
    std::queue<Task> current_task_queue;
};

//多级反馈
struct MFQueue {
    std::queue<Task> m_task_queue;
    int m_slice;
};

class MultiFeedback : public AbstractSchedule {
public:
    MultiFeedback() = default;
    MultiFeedback(const std::vector<Task>& tasks);
    const char* name() { return "多级反馈队列"; }
    void run();
    bool MultiQueueEmpty();

private:
    int m_level;
    int m_slice;
    std::vector<MFQueue> multi_queue_vec;
    RR rr;
};

#endif