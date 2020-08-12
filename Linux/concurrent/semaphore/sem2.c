#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

// 使用信号量完成多值缓冲区问题 比条件变量慢

#define MAX_CONSUMER 10
#define MAX_PRODUCER 10
#define MAX_COUNT 1000000
#define BUFFER_SIZE 200

sem_t full, empty, mutex;

int buffer[BUFFER_SIZE];
int use_size = 0;
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
    int start = MAX_COUNT / MAX_PRODUCER * turn;
    int end = MAX_COUNT / MAX_PRODUCER * (turn + 1);
    for (int i = start; i < end; ++i)
    {
        sem_wait(&empty);
        sem_wait(&mutex);
        put(i);
        sem_post(&mutex);
        sem_post(&full);
    }
    return NULL;
}

void *consumer(void *arg)
{
    int tmp;
    for (int i = 0; i < MAX_COUNT / MAX_CONSUMER; ++i)
    {
        sem_wait(&full);
        sem_wait(&mutex);
        tmp = get();
        ++is_true[tmp];
        sem_post(&mutex);
        sem_post(&empty);
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
    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);
    sem_init(&mutex, 0, 1);
    test();
    judge();
    return 0;
}