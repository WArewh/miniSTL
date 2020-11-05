# 线程私有全局数据ThreadLocal

POSIX线程库通过四个函数操作线程特定数据  
pthread_key_create  创建key  
pthread_key_delete  删除key，数据通过create的时候传递的回调函数销毁  
pthread_getspecific 得到key的value  
pthread_setspecific 设置key的value  

# 线程私有单例ThreadLocalSingleton
基本同singleton，使用到线程私有全局数据

# 线程Thread
start函数调用pthread_create创建线程，线程函数为detail::startThread。
传递给线程函数的参数data是在heap上分配的，data存放了线程要执行的函数func、线程id、线程name等信息。
detail::startThread会调用func启动线程，detail::startThread可以看成是一个跳板或中介。

# 线程池ThreadPool
本质是消费者生产者
vector存储线程，queue存储任务
两个条件变量控制任务个数

start创建n个线程，每个线程都执行runInThread
runInThread是一个循环不断取任务执行
take取任务,空则等待


