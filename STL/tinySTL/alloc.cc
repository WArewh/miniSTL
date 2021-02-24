#include "alloc.h"

namespace mySTL
{

    char* Alloc::start_free = 0;
    char* Alloc::end_free = 0;
    size_t Alloc::heap_size = 0;

    Alloc::obj* Alloc::free_list[FREELISTS] = {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    };



    void* Alloc::allocate(size_t bytes)
    {
        if (bytes > tinyChunk::LIMIT)
        {
            return malloc(bytes);
        }

        size_t index = freelistIndex(bytes);
        obj* list = free_list[index];

        if (list)
        {  // list还有空间给我们
            free_list[index] = list->next;
            return list;
        }

        return refill(roundUp(bytes));  // list没有足够的空间，需要从内存池里面取空间
    }
    void Alloc::deallocate(void* ptr, size_t bytes)
    {
        if (bytes > tinyChunk::LIMIT)
        {
            free(ptr);
        }
        else
        {
            size_t index = freelistIndex(bytes);
            obj* node = static_cast<obj*>(ptr);
            node->next = free_list[index];
            free_list[index] = node;
        }
    }
    void* Alloc::reallocate(void* ptr, size_t old_size, size_t new_size)
    {
        deallocate(ptr, old_size);
        ptr = allocate(new_size);
        return ptr;
    }

    void* Alloc::refill(size_t bytes)
    {
        size_t objs = ADDCOUNT;
        char* chunk = chunkAlloc(bytes, objs);
        obj** now_free_list = 0;
        obj* result = 0;
        obj* cur_obj = 0;
        obj* next_obj = 0;

        if (objs == 1)
        {  //取出的空间只够一个对象使用
            return chunk;
        }
        else
        {
            now_free_list = free_list + freelistIndex(bytes);
            result = (obj*)(chunk);
            *now_free_list = next_obj = (obj*)(chunk + bytes);
            //将取出的多余的空间加入到相应的free_list里面去
            for (int i = 1;; ++i)
            {
                cur_obj = next_obj;
                next_obj = (obj*)((char*)next_obj + bytes);
                if (objs - 1 == i)
                {
                    cur_obj->next = 0;
                    break;
                }
                else
                {
                    cur_obj->next = next_obj;
                }
            }
            return result;
        }
    }

    char* Alloc::chunkAlloc(size_t bytes, size_t& objs)
    {
        char* result = 0;
        size_t total_bytes = bytes * objs;
        size_t bytes_left = end_free - start_free;
        if (bytes_left >= total_bytes)
        {
            result = start_free;
            start_free = start_free + total_bytes;
            return result;
        }
        else if (bytes_left >= bytes)
        {  //内存池剩余空间不能完全满足需要，但足够供应一个或以上的区块
            objs = bytes_left / bytes;
            total_bytes = objs * bytes;
            result = start_free;
            start_free += total_bytes;
            return result;
        }
        else
        {  //内存池剩余空间连一个区块的大小都无法提供
            size_t bytes_to_get = 2 * total_bytes + roundUp(heap_size >> 4);
            if (bytes_left > 0)
            {  //如果有零头剩余,加入适当的list
                obj** now_free_list = free_list + freelistIndex(bytes_left);
                ((obj*)start_free)->next = *now_free_list;
                *now_free_list = (obj*)start_free;
            }
            //补充空间
            start_free = (char*)malloc(bytes_to_get);
            if (!start_free)
            {  //失败,查找目前我们拥有的内存
                obj **now_free_list = 0, *ptr = 0;
                //查找其他list
                for (int i = bytes; i <= tinyChunk::LIMIT; i += tinyChunk::ALIGN)
                {
                    now_free_list = free_list + freelistIndex(i);
                    ptr = *now_free_list;
                    if (ptr != 0)
                    {
                        *now_free_list = ptr->next;
                        start_free = (char*)ptr;
                        end_free = start_free + i;
                        return chunkAlloc(bytes, objs);
                    }
                }
                end_free = 0;
            }
            heap_size += bytes_to_get;
            end_free = start_free + bytes_to_get;
            return chunkAlloc(bytes, objs);
        }
    }
};  // namespace mySTL