#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
//使用指令实现mutex fetch-and-add

// 出现问题：5个线程以上极慢！ 暂且不明白为什么

#define MAXN 10
int share_val = 0;

typedef struct lock_t
{
    int ticket;
    int turn;
} lock_t;

lock_t my_lock;
// 获取并增加(xadd指令)
static inline int fetch_and_add(int *ptr)
{
    int result = 1;
    __asm__ volatile("lock xaddl %0, %1"
                     : "+r"(result), "+m"(*ptr)
                     :
                     : "memory");
    return result;
    // int old_data=*ptr
    // int *prt=old_data+1;
    // return old_data;
}

void lock_init(lock_t *lock)
{
    lock->ticket = 0;
    lock->turn = 0;
}

void lock(lock_t *lock)
{
    int my_ticket = fetch_and_add(&lock->ticket);
    while (my_ticket != lock->turn)
        ;
}
void unlock(lock_t *lock)
{
    fetch_and_add(&lock->turn);
}

void *loop_1000000(void *argv)
{
    for (int i = 0; i < 100; ++i)
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
