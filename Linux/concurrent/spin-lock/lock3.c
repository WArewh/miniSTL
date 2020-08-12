#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// 读者写者锁 读的时候不能写 写的时候不能读 未测试

typedef struct rwlock_t
{
    pthread_mutex_t mutex;
    pthread_mutex_t writer_lock;
    int readers;
} rwlock_t;

void rwlock_init(rwlock_t *rw)
{
    rw->readers = 0;
    pthread_mutex_init(&rw->mutex, NULL);
    pthread_mutex_init(&rw->writer_lock, NULL);
}

void rwlock_reader_lock(rwlock_t *rw)
{
    pthread_mutex_lock(&rw->mutex);
    ++rw->readers;
    if (rw->readers == 1)
        pthread_mutex_lock(&rw->writer_lock); //第一个读者获得锁
    pthread_mutex_unlock(&rw->mutex);
}

void rwlock_reader_unlock(rwlock_t *rw)
{
    pthread_mutex_lock(&rw->mutex);
    --rw->readers;
    if (rw->readers == 0)
        pthread_mutex_unlock(&rw->writer_lock); //没有读者释放锁
    pthread_mutex_unlock(&rw->mutex);
}

void rwlock_writer_lock(rwlock_t *rw)
{
    pthread_mutex_lock(&rw->writer_lock);
}

void rwlock_writer_unlock(rwlock_t *rw)
{
    pthread_mutex_unlock(&rw->writer_lock);
}

int main()
{
    return 0;
}