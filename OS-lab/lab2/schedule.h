#ifndef LAB2_SCEDULE_H
#define LAB2_SCEDULE_H

#include <queue>
#include <vector>

#include "page.h"

class AbstractSchedule {
public:
    AbstractSchedule(const std::vector<Page>& page_vec);
    AbstractSchedule(int size, const std::vector<Page>& page_vec);
    virtual const char* name() = 0;
    virtual void schedule(int index, int no) = 0;
    bool isInTable(int no);
    void calAndPrintPerformance();
    void run();

protected:
    int m_size;                                   //常驻页面个数
    int m_lost;                                   //缺页次数
    std::vector<Page> m_page_vec;                 //序列存储
    std::vector<Page> m_page_table;               //常驻页面
    std::vector<std::vector<Page>> m_statue_vec;  //页面状态
    std::vector<bool> m_miss_vec;                 //记录缺页
};

class FIFO : public AbstractSchedule {
public:
    FIFO(int size, const std::vector<Page>& page_vec) : AbstractSchedule(size, page_vec) {}
    FIFO(const std::vector<Page>& page_vec) : AbstractSchedule(page_vec) {}
    const char* name() { return "先来先服务"; }
    void schedule(int index, int no);
};

class OPT : public AbstractSchedule {
public:
    OPT(int size, const std::vector<Page>& page_vec) : AbstractSchedule(size, page_vec) {}
    OPT(const std::vector<Page>& page_vec) : AbstractSchedule(page_vec) {}
    const char* name() { return "最优调度"; }
    void schedule(int index, int no);
    int findLastAppear(int index, int no);
};

class LRU : public AbstractSchedule {
public:
    LRU(int size, const std::vector<Page>& page_vec) : AbstractSchedule(size, page_vec) {}
    LRU(const std::vector<Page>& page_vec) : AbstractSchedule(page_vec) {}
    const char* name() { return "最近最少使用"; }
    void schedule(int index, int no);
    int findEarlyAppear(int index, int no);
};

#endif
