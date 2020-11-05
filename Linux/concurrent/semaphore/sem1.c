#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
// 实现一个简易信号量
#define MAXN 10

typedef struct sem_t
{
    int value;
    pthread_mutex_t mutex;
    pthread_cond_t cond;
} sem_t;

int share_val;
sem_t sem;

void sem_init(sem_t *sem, int val)
{
    sem->value = val;
    pthread_mutex_init(&sem->mutex, NULL);
    pthread_cond_init(&sem->cond, NULL);
}

void sem_wait(sem_t *sem)
{
    pthread_mutex_lock(&sem->mutex);
    while (sem->value <= 0) //不能先减再增，否则会全员睡眠
        pthread_cond_wait(&sem->cond, &sem->mutex);
    --sem->value;
    pthread_mutex_unlock(&sem->mutex);
}

void sem_post(sem_t *sem)
{
    pthread_mutex_lock(&sem->mutex);
    ++sem->value;
    pthread_cond_signal(&sem->cond);
    pthread_mutex_unlock(&sem->mutex);
}

void *loop_1000000(void *argv)
{
    for (int i = 0; i < 10; ++i)
    {
        sem_wait(&sem);
        share_val++;
        sem_post(&sem);
    }
    return NULL;
}

void test_lock()
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
void*printA(void*arg){
    printf("A");
    sem_post(&sem);
    return NULL;
}

void test_cond()
{
    pthread_t p;
    pthread_create(&p,NULL,printA,NULL);
    sem_wait(&sem);
    printf("B");
}

int main()
{
    sem_init(&sem, 1); // 二值信号量
    test_lock();
    sem_init(&sem, 0); //条件变量
    test_cond();
    return 0;
}