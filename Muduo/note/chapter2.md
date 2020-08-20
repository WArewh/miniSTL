# Chapter2 线程同步

## 知识点

### 同步原语提示
推荐使用非可重入的mutex，这样可以在早期就发现问题以及思考对锁的需求
使用条件变量需要防止虚假唤醒的发生
尽量不要使用读写锁，如果对并发读写有高要求可以使用read-copy-update
也尽量不要使用信号量，mutex和condtion结合可以解决，如果要控制并发度可以用线程池
gdb调试可以使用thread apply all bt，来查看调用栈
用PTHREAD_MUTEX_ERRORCHECK_NP查看错误(mutexLock带debug选项)

read-copy-update
读操作不需要获得任何锁就可以访问，但写操作在访问它时首先拷贝一个副本，然后对副本进行修改，最后在适当的时机(所有CPU都结束对共享数据的操作)把指向原来数据的指针重新指向新的被修改的数据。

### 安全的单例模式
双检查锁由于指令重排可能导致失效，可以使用pthread_once保证安全

### 优化策略
对于读端，用局部变量将共享变量进行拷贝，减小临界区的范围(可能读到的是旧数据)
对于写端，如果共享变量被独占直接修改，有其他人读写就拷贝一份进行修改
```
// 伪代码
class foo;
shared_ptr<vector<foo>>global_foo_vec_ptr;
mutexLock mutex;

void printAll(){
    shared_ptr<vector<foo>>temp_foo_vec_ptr;
    {
        mutexLockGuard lock(mutex);
        temp_foo_vec_ptr=global_foo_vec_ptr;
    }
    // print...
}

void post(const&foo f){
    mutexLockGuard lock(mutex);
    if(!global_foo_vec_ptr.unique()){//没有独占
        //因为源没有被独占，因此reset后，源没有被销毁，其他已获得源的线程可以继续读，所有线程读完后源销毁
        global_foo_vec_ptr.reset(new vector<foo>(*global_foo_vec_ptr));//新的源
    }
    global_foo_vec_ptr->push_back(f);
}
```




