#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
// 两线程交替打印
pthread_mutex_t mutex;
pthread_cond_t cond;
int share_val = 0;

void *print_upper(void *arg)
{
    for (int i = 0; i < 26; ++i)
    {
        pthread_mutex_lock(&mutex);           // U1
        while (share_val != 0)                // U2
            pthread_cond_wait(&cond, &mutex); // U3
        printf("%c", 'A' + i);                // U4
        share_val = 1;                        // U5
        pthread_cond_signal(&cond);           // U6
        pthread_mutex_unlock(&mutex);         // U7
    }
    return NULL;
}

void *print_lower(void *arg)
{
    for (int i = 0; i < 26; ++i)
    {
        pthread_mutex_lock(&mutex);           // L1
        while (share_val != 1)                // L2
            pthread_cond_wait(&cond, &mutex); // L3
        printf("%c", 'a' + i);                // L4
        share_val = 0;                        // L5
        pthread_cond_signal(&cond);           // L6
        pthread_mutex_unlock(&mutex);         // L7
    }
    return NULL;
}
void test()
{
    pthread_t p1, p2;
    pthread_create(&p1, NULL, print_upper, NULL);
    pthread_create(&p2, NULL, print_lower, NULL);
    pthread_join(p1, NULL);
    pthread_join(p2, NULL);
}

int main()
{
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&cond, NULL);
    test();
    return 0;
}