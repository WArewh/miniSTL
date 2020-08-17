#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>

// 信号量实现读者写者锁 两个二值信号量
// 信号量实现哲学家就餐 二值信号量

// 解决方式：有一个人改变握叉子的顺序或者将握叉子改为原子 未测试

#define PEOPLE 5
#define THINK_TIME 1000
#define EAT_TIME 2000

sem_t forks[PEOPLE];

void forks_init() {
    for (int i = 0; i < PEOPLE; ++i) {
        sem_init(&forks[i], 0, 1);
    }
}

int left_fork(int pos) {
    return pos;
}

int right_fork(int pos) {
    return (pos + 1) % PEOPLE;
}

void getfork(int pos) {
    if (pos == PEOPLE - 1)  //最后一个人改变握叉子的顺序
    {
        sem_wait(&forks[right_fork(pos)]);
        sem_wait(&forks[left_fork(pos)]);
    } else {
        sem_wait(&forks[left_fork(pos)]);
        sem_wait(&forks[right_fork(pos)]);
    }
}

void putfork(int pos) {
    sem_post(&forks[left_fork(pos)]);
    sem_post(&forks[right_fork(pos)]);
}

void think() {
    for (int i = 0; i < THINK_TIME; ++i)
        ;
}

void eat() {
    for (int i = 0; i < EAT_TIME; ++i)
        ;
}

int main() {
    forks_init();
    return 0;
}