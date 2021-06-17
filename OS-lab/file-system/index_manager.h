#ifndef LAB_INDEX_MANAGER_H_
#define LAB_INDEX_MANAGER_H_

#include <stack>

#include "disk.h"
#include "index_node.h"

using std::stack;

const uint32_t I_MAP_START = 34 * BLOCK_SIZE;
const uint32_t I_MAP_COUNT = 344 * BLOCK_SIZE / sizeof(IndexNode);
const uint32_t I_MAP_SIZE = I_MAP_COUNT;
const uint32_t I_MAP_END = I_MAP_START + I_MAP_SIZE;

class IndexManager
{
public:
    IndexManager(Disk&);
    ~IndexManager();
    void initStack();

public:
    uint32_t getIndex();
    void freeIndex(uint32_t index);

private:
    Disk disk;
    uint32_t m_pos;
    stack<uint32_t> m_unused;
    bool m_map[I_MAP_COUNT];
};

#endif