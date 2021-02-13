#ifndef CREATIONAL_SINGLETON_STAGE1_H_
#define CREATIONAL_SINGLETON_STAGE1_H_

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
    virtual ~Singleton();
};

/*

// 模板
template <class T>
class Singleton {
public:
    Singleton() = default;
    Singleton(const Singleton&) = delete;
    Singleton(Singleton&&) = delete;
    Singleton& operator=(const Singleton&) = delete;
    Singleton& operator=(Singleton&&) = delete;
    virtual ~Singleton() = default;

public:
    static T& GetInstance() {
        static T s_instance;
        return s_instance;
    }
};

*/


#endif