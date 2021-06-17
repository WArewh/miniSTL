#ifndef LAB_DATA_H_
#define LAB_DATA_H_

#include <cstring>

#include "disk.h"

extern Disk disk;

const uint32_t D_START = 384 * BLOCK_SIZE;
const uint32_t D_COUNT = 16000;
const uint32_t D_SIZE = D_COUNT * BLOCK_SIZE;
const uint32_t D_END = D_START + D_SIZE;


struct DataBlock
{
public:
    DataBlock();
    char* data() { return m_data; }
    uint32_t* index() { return m_index; }

public:
    union
    {
        char m_data[BLOCK_SIZE / sizeof(char)];
        uint32_t m_index[BLOCK_SIZE / sizeof(uint32_t)];
    };
};


#endif