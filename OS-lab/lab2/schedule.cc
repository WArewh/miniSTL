#include "schedule.h"

#include <stdio.h>

AbstractSchedule::AbstractSchedule(int size, const std::vector<Page>& page_vec)
    : m_size(size),
      m_lost(0) {
    for (auto p : page_vec) {
        m_page_vec.push_back(p);
    }
}

AbstractSchedule::AbstractSchedule(const std::vector<Page>& page_vec) : m_size(3), m_lost(0) {
    for (auto p : page_vec) {
        m_page_vec.push_back(p);
    }
}

void AbstractSchedule::calAndPrintPerformance() {
    for (const auto& p : m_page_vec) {
        printf("%-5d", p.m_no);
    }
    printf("\n\n");
    for (int i = 0; i < m_size; ++i) {
        for (int j = 0; j < m_page_vec.size(); ++j) {
            int no = m_statue_vec[j][i].m_no;
            if (no != -1) {
                printf("%-5d", no);
            } else {
                printf("-    ");
            }
        }
        printf("\n");
    }
    printf("\n");
    for (auto b : m_miss_vec) {
        if (b == true) {
            printf("*    ");
        } else {
            printf("     ");
        }
    }
    printf("\n\n");
    printf("缺页率为:%d/%d = %.2f%%\n", m_lost, (int)m_page_vec.size(),
           1.0 * m_lost / m_page_vec.size() * 100);
    printf("\n");
}

void AbstractSchedule::run() {
    for (int i = 0; i < m_page_vec.size(); ++i) {
        int cur_no = m_page_vec[i].m_no;
        if (!isInTable(cur_no)) {  //不在页表中
            m_lost += 1;
            m_miss_vec.push_back(true);
            schedule(i, cur_no);
        } else {  //在页表中
            m_miss_vec.push_back(false);
        }


        std::vector<Page> temp = m_page_table;
        while (temp.size() < m_size) {
            temp.push_back(Page(-1));
        }
        m_statue_vec.push_back(temp);
    }
}

bool AbstractSchedule::isInTable(int no) {
    for (auto p : m_page_table) {
        if (p.m_no == no)
            return true;
    }
    return false;
}

void FIFO::schedule(int index, int no) {
    if (m_page_table.size() < m_size) {
        m_page_table.push_back(Page(no));
    } else {
        m_page_table.erase(m_page_table.begin());
        m_page_table.push_back(Page(no));
    }
}

// index之后最后出现的位置
void OPT::schedule(int index, int no) {
    if (m_page_table.size() < m_size) {
        m_page_table.push_back(Page(no));
    } else {
        int replace_index = 0;
        int last_pos = 0;
        for (int i = 0; i < m_page_table.size(); ++i) {
            int cur_no = m_page_table[i].m_no;
            if (findLastAppear(index, cur_no) > last_pos) {
                last_pos = findLastAppear(index, cur_no);
                replace_index = i;
            }
        }
        m_page_table[replace_index].m_no = no;
    }
}

int OPT::findLastAppear(int index, int no) {
    for (int i = index; i < m_page_vec.size(); ++i) {
        int cur_no = m_page_vec[i].m_no;
        if (cur_no == no)
            return i;
    }
    return m_page_vec.size() + 1;
}

// index之前最早出现的位置
void LRU::schedule(int index, int no) {
    if (m_page_table.size() < m_size) {
        m_page_table.push_back(Page(no));
    } else {
        int replace_index = 0;
        int first_pos = m_page_table.size() + 1;
        for (int i = 0; i < m_page_table.size(); ++i) {
            int cur_no = m_page_table[i].m_no;
            if (findEarlyAppear(index, cur_no) < first_pos) {
                first_pos = findEarlyAppear(index, cur_no);
                replace_index = i;
            }
        }
        m_page_table[replace_index].m_no = no;
    }
}


int LRU::findEarlyAppear(int index, int no) {
    for (int i = index - 1; i >= 0; --i) {
        int cur_no = m_page_vec[i].m_no;
        if (cur_no == no)
            return i;
    }
    return index;
}