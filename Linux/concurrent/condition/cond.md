条件变量是一个显式队列，当条件不满足，把自己加入队列，等待直到被唤醒。
相关API：
pthread_cond_wait(&cond,&mutex);
作用：加入队列，释放锁并睡眠(原子的,时机在于操作系统把他放在线程等待队列之后)，随后等到被唤醒，重新获得锁。

pthread_cond_signal(&cond);
作用：唤醒条件变量上堵塞的一个线程(可能会唤醒多个线程)

唤醒多个线程的原因：
Linux中pthread_cond_wait是用futex(慢速)系统调用实现的. 而进程收到信号后, 每个阻塞的系统调用(类似wait, read, recv)都会立马返回(错误码EINTR)。

唤醒多个可能会造成虚假唤醒，需要用while而不是if

