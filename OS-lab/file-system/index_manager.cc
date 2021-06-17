#include "index_manager.h"

IndexManager::IndexManager(Disk& d) : disk(d)
{
    disk.Read(I_MAP_END, &m_pos, sizeof(uint32_t), 1);
    disk.Read(I_MAP_START, m_map, sizeof(bool), I_MAP_COUNT);
    initStack();
}

void IndexManager::initStack()
{
    for (int i = 0; i < m_pos; ++i)
    {
        if (m_map[i] == false)
        {
            m_unused.push(i);
        }
    }
}

uint32_t IndexManager::getIndex()
{
    if (!m_unused.empty())
    {
        uint32_t res = m_unused.top();
        m_unused.pop();
        m_map[res] = true;
        return res;
    }
    if (m_pos < I_MAP_COUNT)
    {
        m_map[m_pos] = true;
        return m_pos++;
    }
    return -1;
}
void IndexManager::freeIndex(uint32_t index)
{
    m_unused.push(index);
    m_map[index] = false;
}

IndexManager::~IndexManager()
{
    disk.Write(I_MAP_END, &m_pos, sizeof(uint32_t), 1);
    disk.Write(I_MAP_START, m_map, sizeof(bool), I_MAP_COUNT);
}