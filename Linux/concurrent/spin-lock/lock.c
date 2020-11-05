#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MAXN 10

int share_val = 0;

pthread_mutex_t my_lock;

void *loop_1000000(void *argv)
{
    for (int i = 0; i < 1000000; ++i)
    {
        pthread_mutex_lock(&my_lock);
        share_val++;
        pthread_mutex_unlock(&my_lock);
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
    pthread_mutex_init(&my_lock, NULL);
    test();
    return 0;
}