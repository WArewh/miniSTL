
#include "schedule.h"

#include <algorithm>

#include "display.h"

AbstractSchedule::AbstractSchedule(const std::vector<Task>& tasks) : current_time(0) {
    for (auto task : tasks) {
        m_task_queue.push(task);
    }
}

void AbstractSchedule::calAndPrintPerformance() {
    float aver_turn_time = 0.0;
    float aver_right_turn_time = 0.0;
    for (auto t : cal_vec) {
        float turn_time = 1.0 * (t.m_finish - t.m_arrival);
        float right_turn_time = 1.0 * (t.m_finish - t.m_arrival) / t.m_require;
        aver_turn_time += turn_time;
        aver_right_turn_time += right_turn_time;
    }
    printf("平均周转时间:%.3f\n", aver_turn_time / cal_vec.size());
    printf("平均带权周转时间:%.3f\n", aver_right_turn_time / cal_vec.size());
    printf("***************************************\n");
}

bool FIFO_compare::operator()(const Task& t1, const Task& t2) {
    if (t1.m_arrival == t2.m_arrival)
        return t1.m_require > t2.m_require;
    return t1.m_arrival > t2.m_arrival;
}

FIFO::FIFO(const std::vector<Task>& tasks) : AbstractSchedule(tasks) {
}
void FIFO::run() {
    while (!m_task_queue.empty() || !current_task_queue.empty()) {
        //将已经到达的任务添加进执行队列
        while (!m_task_queue.empty() && m_task_queue.top().m_arrival <= current_time) {
            current_task_queue.push(m_task_queue.top());
            m_task_queue.pop();
        }
        if (!current_task_queue.empty()) {
            auto t = current_task_queue.top();
            printSchedule(current_time, t);
            current_time += t.m_require;
            current_task_queue.pop();
            t.m_finish = current_time;
            cal_vec.push_back(t);
        } else {
            if (!m_task_queue.empty()) {  //当前没有任务需要等待到下一个任务到来
                auto t = m_task_queue.top();
                current_time = t.m_arrival;
                printSchedule(current_time, t);
                current_time += t.m_require;
                m_task_queue.pop();
                t.m_finish = current_time;
                cal_vec.push_back(t);
            }
        }
    }
}

bool SJF_compare::operator()(const Task& t1, const Task& t2) {
    return t1.m_require > t2.m_require;
}

SJF::SJF(const std::vector<Task>& tasks) : AbstractSchedule(tasks) {
}
void SJF::run() {
    while (!m_task_queue.empty() || !current_task_queue.empty()) {
        //任务执行完将已经到达的任务添加进执行队列
        while (!m_task_queue.empty() && m_task_queue.top().m_arrival <= current_time) {
            current_task_queue.push(m_task_queue.top());
            m_task_queue.pop();
        }
        if (!current_task_queue.empty()) {
            auto t = current_task_queue.top();
            printSchedule(current_time, t);
            current_time += t.m_require;
            current_task_queue.pop();
            t.m_finish = current_time;
            cal_vec.push_back(t);
        } else {
            if (!m_task_queue.empty()) {  //当前没有任务需要等待到下一个任务到来
                auto t = m_task_queue.top();
                current_time = t.m_arrival;
                printSchedule(current_time, t);
                current_time += t.m_require;
                m_task_queue.pop();
                t.m_finish = current_time;
                cal_vec.push_back(t);
            }
        }
    }
}

bool PP_compare::operator()(const Task& t1, const Task& t2) {
    if (t1.m_priority == t2.m_priority)
        return t1.m_require > t2.m_require;
    return t1.m_priority > t2.m_priority;
}

PP::PP(const std::vector<Task>& tasks) : AbstractSchedule(tasks) {
}

void PP::run() {

    while (!m_task_queue.empty() || !current_task_queue.empty()) {
        //任务执行完将已经到达的任务添加进执行队列
        while (!m_task_queue.empty() && m_task_queue.top().m_arrival <= current_time) {
            current_task_queue.push(m_task_queue.top());
            m_task_queue.pop();
        }
        if (!current_task_queue.empty()) {
            auto t = current_task_queue.top();
            printSchedule(current_time, t);
            current_time += t.m_require;
            current_task_queue.pop();
            t.m_finish = current_time;
            cal_vec.push_back(t);
        } else {
            if (!m_task_queue.empty()) {  //当前没有任务需要等待到下一个任务到来
                auto t = m_task_queue.top();
                current_time = t.m_arrival;
                printSchedule(current_time, t);
                current_time += t.m_require;
                m_task_queue.pop();
                t.m_finish = current_time;
                cal_vec.push_back(t);
            }
        }
    }
}

RR::RR(int slice, const std::vector<Task>& tasks) : AbstractSchedule(tasks), m_slice(slice) {
}

RR::RR(const std::vector<Task>& tasks) : AbstractSchedule(tasks), m_slice(1) {
}

void RR::run() {

    while (!m_task_queue.empty() || !current_task_queue.empty()) {
        //任务执行完将已经到达的任务添加进执行队列
        while (!m_task_queue.empty() && m_task_queue.top().m_arrival <= current_time) {
            current_task_queue.push(m_task_queue.top());
            m_task_queue.pop();
        }
        if (!current_task_queue.empty()) {
            auto& t = current_task_queue.front();

            int execute_time = std::min(t.m_require - t.m_already, m_slice);
            t.m_already += execute_time;
            printSchedule(current_time, t);
            current_time += execute_time;
            if (t.m_already < t.m_require) {
                current_task_queue.push(t);
            } else {
                t.m_finish = current_time;
                cal_vec.push_back(t);
            }
            current_task_queue.pop();
        } else {
            if (!m_task_queue.empty()) {  //当前没有任务需要等待到下一个任务到来
                auto t = m_task_queue.top();
                int execute_time = std::min(t.m_require - t.m_already, m_slice);
                current_time = t.m_arrival;
                t.m_already += execute_time;
                printSchedule(current_time, t);
                current_time += execute_time;
                if (t.m_already < t.m_require) {
                    current_task_queue.push(t);
                } else {
                    t.m_finish = current_time;
                    cal_vec.push_back(t);
                }
                m_task_queue.pop();
            }
        }
    }
}

MultiFeedback::MultiFeedback(const std::vector<Task>& tasks)
    : m_level(3),
      m_slice(1),
      AbstractSchedule(tasks) {
    multi_queue_vec.resize(m_level - 1);

    int length = 1;
    for (int i = 0; i < m_level - 1; ++i) {
        multi_queue_vec[i].m_slice = length;
        length *= 2;
    }
    rr.setSlice(length);
}

bool MultiFeedback::MultiQueueEmpty() {
    for (int i = 0; i < m_level - 1; ++i) {
        if (!multi_queue_vec[i].m_task_queue.empty()) {
            return false;
        }
    }
    return true;
}

void MultiFeedback::run() {

    while (!m_task_queue.empty() || !MultiQueueEmpty()) {
        //任务执行完将已经到达的任务添加进执行队列
        while (!m_task_queue.empty() && m_task_queue.top().m_arrival <= current_time) {
            multi_queue_vec[0].m_task_queue.push(m_task_queue.top());
            m_task_queue.pop();
        }

        int current_level = 0;
        for (int i = 0; i < m_level - 1; ++i) {
            if (!multi_queue_vec[i].m_task_queue.empty()) {
                current_level = i;
                break;
            }
        }

        if (!multi_queue_vec[current_level].m_task_queue.empty()) {
            auto t = multi_queue_vec[current_level].m_task_queue.front();
            int execute_time =
                std::min(t.m_require - t.m_already, multi_queue_vec[current_level].m_slice);

            t.m_already += execute_time;
            printSchedule(current_time, t);
            current_time += execute_time;
            if (t.m_already < t.m_require) {
                if (current_level + 1 < m_level - 1)
                    multi_queue_vec[current_level + 1].m_task_queue.push(t);
                else
                    rr.getQueue().push(t);
            } else {
                t.m_finish = current_time;
                cal_vec.push_back(t);
            }
            multi_queue_vec[current_level].m_task_queue.pop();
        } else {
            if (!m_task_queue.empty()) {  //当前没有任务需要等待到下一个任务到来
                auto t = m_task_queue.top();
                int execute_time =
                    std::min(t.m_require - t.m_already, multi_queue_vec[current_level].m_slice);

                current_time = t.m_arrival;
                t.m_already += execute_time;
                printSchedule(current_time, t);
                current_time += execute_time;

                if (t.m_already < t.m_require) {
                    multi_queue_vec[1].m_task_queue.push(t);
                } else {
                    t.m_finish = current_time;
                    cal_vec.push_back(t);
                }
                m_task_queue.pop();
            }
        }
    }
    rr.setCurrentTime(current_time);
    rr.run();
    for (auto t : rr.getCalVec()) {
        cal_vec.push_back(t);
    }
}