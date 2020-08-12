#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
// 使用指令实现mutex test-and-set compare-and-swap

#define MAXN 5

int share_val = 0;

typedef struct lock_t
{
    int is_lock;
} lock_t;

lock_t my_lock;

// 测试并设置(xchg指令) 返回旧值，更新新值
// "cc"：你使用的指令会改变CPU的条件寄存器cc
static inline int test_and_set(int *old_ptr, int new_data)
{
    int result;
    __asm__ volatile("lock; xchgl %0, %1"
                     : "+m"(*old_ptr), "=a"(result)
                     : "1"(new_data)
                     : "cc");
    return result;
    // int result=*old_ptr;
    // *old_ptr=new_data;
    // return result;
}
// 比较并交换(cmpxchgl指令)
static inline int compare_and_swap(int *ptr, int old_data, int new_data)
{
    int result;
    __asm__ volatile(
        "lock cmpxchgl %1,%2"
        : "=a"(result)
        : "r"(new_data), "m"(*ptr), "0"(old_data)
        : "memory");
    return result;
    // int result=*ptr;
    // if(result==expect_data)
    //     *ptr=new_data;
    // return result;
}

void lock_init(lock_t *lock)
{
    lock->is_lock = 0;
}

void lock(lock_t *lock)
{
    while (test_and_set(&lock->is_lock, 1))
        ;
    // while (compare_and_swap(&lock->is_lock, 0, 1) == 1)
    //     ;
}
void unlock(lock_t *lock)
{
    lock->is_lock = 0;
}

void *loop_1000000(void *argv)
{
    for (int i = 0; i < 1000000; ++i)
    {
        lock(&my_lock);
        share_val++;
        unlock(&my_lock);
    }
    return NULL;
}

void test()
{
    pthread_t p[MAXN];
    for (int i = 0; i < MAXN; ++i)
    {
        pthread_create(&p[i], NULL, loop_1000000, NULL);
    }
    for (int i = 0; i < MAXN; ++i)
    {
        pthread_join(p[i], NULL);
    }
    printf("%d\n", share_val);
}

int main()
{
    lock_init(&my_lock);
    test();
    return 0;
}
