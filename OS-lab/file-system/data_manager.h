#ifndef LAB_DATA_MANAGER_H_
#define LAB_DATA_MANAGER_H_

#include <stack>

#include "data.h"
#include "disk.h"

using std::stack;

const uint32_t D_MAP_START = 2 * BLOCK_SIZE;
const uint32_t D_MAP_COUNT = 16000;
const uint32_t D_MAP_SIZE = D_MAP_COUNT;
const uint32_t D_MAP_END = D_MAP_START + D_MAP_SIZE;

class DataManager
{
public:
    DataManager(Disk&);
    ~DataManager();
    void initStack();

public:
    uint32_t getIndex();
    void freeIndex(uint32_t index);

private:
    Disk disk;
    uint32_t m_pos;
    stack<uint32_t> m_unused;
    bool m_map[D_MAP_COUNT];
};

#endif