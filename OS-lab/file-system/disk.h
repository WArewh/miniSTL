#ifndef LAB_DISK_H_
#define LAB_DISK_H_

#include <unistd.h>

#include <cstdint>
#include <cstdio>

const int BLOCK_SIZE = 512;

class Disk
{
public:
    Disk(const char* path);
    ~Disk();

public:
    int Read(uint32_t start, void* ptr, size_t size, uint32_t cnt);
    int Write(uint32_t start, void* ptr, size_t size, uint32_t cnt);

private:
    FILE* m_disk;
};

#endif