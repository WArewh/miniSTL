#ifndef _MYSTL_ALLOC_H
#define _MYSTL_ALLOC_H

#include <cstdlib>

namespace mySTL
{
    /*
     * 空间配置器(STL源码解析第二章)
     * 使用内存池分配小于128字节的空间
     * 大于128直接使用malloc和free
     */
    class Alloc
    {
    public:
        static void* allocate(size_t bytes);
        static void deallocate(void* ptr, size_t bytes);
        static void* reallocate(void* ptr, size_t old_size, size_t new_size);

    private:
        enum tinyChunk  // 小型区块参数
        {
            ALIGN = 8,                  // 小型区块的上调边界
            LIMIT = 128,                // 小型区块的上限,超过使用malloc
            FREELISTS = LIMIT / ALIGN,  // freelist个数
            ADDCOUNT = 20               // 每次添加的数量
        };

    private:
        // free-lists的节点构造
        union obj
        {
            union obj* next;
            char client[1];
        };
        static char* start_free;  // 内存池起始位置
        static char* end_free;    // 内存池结束位置
        static size_t heap_size;
        static obj* free_list[FREELISTS];

    private:
        //将bytes上调至8的倍数
        static size_t roundUp(size_t bytes) { return ((bytes + ALIGN - 1) & ~(ALIGN - 1)); }
        //根据区块大小，决定使用第n号free-list
        static size_t freelistIndex(size_t bytes) { return (((bytes) + ALIGN - 1) / ALIGN - 1); }
        //返回一个大小为n的对象
        static void* refill(size_t bytes);
        //配置一大块空间，可容纳objs个大小为size的区块
        //如果空间不够获得的数量小于20
        static char* chunkAlloc(size_t bytes, size_t& objs);
    };

}  // namespace mySTL

#endif