#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
// 单值缓冲区问题
// 注意 消费者需要提醒生产者 生产者提醒消费者
// 因此需要两个条件变量
// 如果不使用两个条件变量会造成生产者提醒生产者或消费者提醒消费者的情况，导致全员睡眠
// 使用一个条件变量也可以用boardcast全体唤醒来达到目的，但是成本较高

#define MAX_CONSUMER 5
#define MAX_PRODUCER 5
#define MAX_COUNT 10000

int buffer = 0;
int use_size = 0;

pthread_mutex_t mutex;
pthread_cond_t empty, fill;
// 缓存区空，说明要提醒生产者
// 缓存区满，说明要提醒消费者

int is_true[MAX_COUNT];

int get()
{
    use_size = 0;
    return buffer;
}
void put(int val)
{
    use_size = 1;
    buffer = val;
}

void *producer(void *arg)
{
    long turn = (long)arg;
    int start = MAX_COUNT / MAX_PRODUCER * turn;
    int end = MAX_COUNT / MAX_PRODUCER * (turn + 1);
    for (int i = start; i < end; ++i)
    {
        pthread_mutex_lock(&mutex);
        while (use_size == 1)
            pthread_cond_wait(&empty, &mutex);
        put(i);
        pthread_cond_signal(&fill);
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

void *consumer(void *arg)
{
    int tmp;
    for (int i = 0; i < MAX_COUNT / MAX_CONSUMER; ++i)
    {
        pthread_mutex_lock(&mutex);
        while (use_size == 0)
            pthread_cond_wait(&fill, &mutex);
        tmp = get();
        ++is_true[tmp];
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