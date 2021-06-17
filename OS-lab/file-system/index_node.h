#ifndef LAB_INDEX_NODE_H_
#define LAB_INDEX_NODE_H_

#include <cstdint>
#include <cstring>
#include <string>

#include "disk.h"

using std::string;

const uint32_t F_MAX_LENGTH = 16;

extern Disk disk;

// 16+24+24 = 64
class IndexNode
{
public:
    IndexNode() {}
    IndexNode(const IndexNode& node);
    IndexNode(string name, uint32_t index);
    ~IndexNode();

public:
    char m_name[F_MAX_LENGTH];
    uint32_t m_index;
    uint32_t m_size;
    uint32_t m_capacity;
    uint32_t m_direct[4];  //一级索引
    char m_reserve[20];
};

const uint32_t I_START = 40 * BLOCK_SIZE;
const uint32_t I_SIZE = 344 * BLOCK_SIZE;
const uint32_t I_COUNT = I_SIZE / sizeof(IndexNode);
const uint32_t I_END = I_START + I_SIZE;

#endif