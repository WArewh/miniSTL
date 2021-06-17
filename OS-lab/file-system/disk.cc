#include "disk.h"
Disk::Disk(const char* path)
{
    m_disk = fopen(path, "r+");
    if (m_disk == nullptr)
    {
        printf("请重新设置path");
    }
}

Disk::~Disk()
{
    fclose(m_disk);
}

int Disk::Read(uint32_t start, void* ptr, size_t size, uint32_t cnt)
{
    fseek(m_disk, start, SEEK_SET);
    int res = fread(ptr, size, cnt, m_disk);
    fflush(m_disk);
    return res;
}

int Disk::Write(uint32_t start, void* ptr, size_t size, uint32_t cnt)
{
    fseek(m_disk, start, SEEK_SET);
    int res = fwrite(ptr, size, cnt, m_disk);
    fflush(m_disk);
    return res;
}