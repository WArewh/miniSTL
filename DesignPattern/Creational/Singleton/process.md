# 背景
小W在某个项目中使用了抽象工厂这个设计模式，需要把工厂这个类写为单例，小W采用了懒汉模式

## 懒汉和饿汉
懒汉模式：需要的时候才创建，会加快程序启动速度，需要保证线程安全
饿汉模式：程序一运行，我就创建好对象，会减慢程序启动速度，天生线程安全

## 线程安全的单例
### solution1
```
std::mutex mt;
class Singleton
{
private:
    Singleton(){}
public:
    static Singleton* instance()
    {
        mt.lock();  // 加锁
        if(m_instance == 0)
            m_instance = new Singleton();
        mt.unlock();  // 解锁
        return m_instance;
    }
private:
    static Singleton* m_instance;
};
Singleton* Singleton::m_instance = nullptr;
```

### analyse
解决了线程安全问题，但是资源浪费比较严重

### solution2
```
class Singleton {
public:
    /* 
    注意返回的是引用
    指针和引用在语法上的最大区别就是指针可以为NULL，可以通过delete运算符删除指针所指的实例，而引用则不可以。
    */

    static Singleton& getInstance() {
        static Singleton instance;  //静态局部变量
        return instance;
    }

private:
    Singleton() = default;
    Singleton(const Singleton& other) = delete;
    Singleton(Singleton&& other) = delete;
    Singleton& operator=(const Singleton&) = delete;
    Singleton& operator=(Singleton&&) = delete;
};

```

### analyse
C++11以后的最简洁的跨平台方案，局部静态变量不仅只会初始化一次，而且还是线程安全的。(C++11标准保证)


