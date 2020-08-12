#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
// 多值缓冲区问题 简单优化

#define MAX_CONSUMER 10
#define MAX_PRODUCER 10
#define MAX_COUNT 1000000
#define BUFFER_SIZE 200

int buffer[BUFFER_SIZE];
int use_size = 0;

pthread_mutex_t mutex;
pthread_cond_t empty, fill;

int is_true[MAX_COUNT];

int get()
{
    int val = buffer[--use_size];
    return val;
}
void put(int val)
{
    buffer[use_size++] = val;
}

void *producer(void *arg)
{
    long turn = (long)arg;
    int flag = 0;
    int start = MAX_COUNT / MAX_PRODUCER * turn;
    int end = MAX_COUNT / MAX_PRODUCER * (turn + 1);
    for (int i = start; i < end; ++i)
    {
        flag = 0;
        pthread_mutex_lock(&mutex);
        while (use_size == BUFFER_SIZE)
            pthread_cond_wait(&empty, &mutex);
        while (use_size != BUFFER_SIZE)
        {
            put(i++);
            flag = 1;
        }
        if (flag == 1)
            --i;
        pthread_cond_signal(&fill);
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

void *consumer(void *arg)
{
    int tmp;
    int flag = 1;
    for (int i = 0; i < MAX_COUNT / MAX_CONSUMER; ++i)
    {
        flag = 0;
        pthread_mutex_lock(&mutex);
        while (use_size == 0)
            pthread_cond_wait(&fill, &mutex);
        while (use_size != 0)
        {
            tmp = get();
            ++is_true[tmp];
            ++i;
            flag = 1;
        }
        if (flag == 1)
            --i;
        pthread_cond_signal(&empty);
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

void test()
{
    pthread_t con[MAX_CONSUMER];
    pthread_t pro[MAX_PRODUCER];

    for (long i = 0; i < MAX_PRODUCER; ++i)
    {
        pthread_create(&pro[i], NULL, producer, (void *)i);
    }
    for (long i = 0; i < MAX_CONSUMER; ++i)
    {
        pthread_create(&con[i], NULL, consumer, NULL);
    }
    for (long i = 0; i < MAX_PRODUCER; ++i)
    {
        pthread_join(pro[i], NULL);
    }
    for (long i = 0; i < MAX_CONSUMER; ++i)
    {
        pthread_join(con[i], NULL);
    }
}

void judge()
{
    for (int i = 0; i < MAX_COUNT; ++i)
    {
        if (is_true[i] != 1)
        {
            printf("false %d\n", i);
            return;
        }
    }
    printf("true\n");
}

int main()
{
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&empty, NULL);
    pthread_cond_init(&fill, NULL);
    test();
    judge();
    return 0;
}