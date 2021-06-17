#include "data_manager.h"

#include "disk.h"

DataManager::DataManager(Disk& d) : disk(d)
{
    disk.Read(D_MAP_END, &m_pos, sizeof(uint32_t), 1);
    disk.Read(D_MAP_START, m_map, sizeof(bool), D_COUNT);
    initStack();
}

void DataManager::initStack()
{
    for (int i = 0; i < m_pos; ++i)
    {
        if (m_map[i] == false)
        {
            m_unused.push(i);
        }
    }
}

uint32_t DataManager::getIndex()
{
    if (!m_unused.empty())
    {
        uint32_t res = m_unused.top();
        m_unused.pop();
        m_map[res] = true;
        return res;
    }
    if (m_pos < D_COUNT)
    {
        m_map[m_pos] = true;
        return m_pos++;
    }
    return -1;
}
void DataManager::freeIndex(uint32_t index)
{
    m_unused.push(index);
    m_map[index] = false;
}

DataManager::~DataManager()
{
    disk.Write(D_MAP_END, &m_pos, sizeof(uint32_t), 1);
    disk.Write(D_MAP_START, m_map, sizeof(bool), D_COUNT);
}