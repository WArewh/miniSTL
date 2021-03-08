#include <iostream>
#include <string>
using namespace std;

/*

为了实现虚函数，C++使用一种称为虚函数表的特殊形式的后期绑定。
该虚函数表是用于解决在动态/后期绑定方式的函数调用函数的查找表。

每个使用虚函数的类(或者从使用虚函数的类派生)都有自己的虚拟表。
该表只是编译器在编译时设置的静态数组。
虚拟表包含可由类的对象调用的每个虚函数的一个条目。
此表中的每个条目只是一个函数指针，指向该类可访问的派生函数。

其次，编译器还会添加一个隐藏指向基类的指针，我们称之为vptr。
vptr在创建类实例时自动设置，以便指向该类的虚拟表。
与this指针不同，this指针实际上是编译器用来解析自引用的函数参数，没有真实存在，而vptr是一个真正的指针。

虚析构函数原理
将析构函数加入虚函数表中，因为调用子类析构会调用父类析构，因此得以实现
*/
typedef void (*Fun)();
class A
{
public:
    virtual void func1() { cout << "A::fun1()" << endl; }
    virtual void func2() { cout << "A::fun2()" << endl; }
    virtual void func3() { cout << "A::fun3()" << endl; }
    virtual ~A() { cout << "~A()" << endl; }
};
/*
A的虚函数表
A::func1()
A::func2()
A::func3()
~A()
*/

class B : public A
{
public:
    virtual void func1() { cout << "B::fun1()" << endl; }
    virtual void func2() { cout << "B::fun2()" << endl; }
    virtual ~B() { cout << "~B()" << endl; }
};
/*
B的虚函数表
B::func1()
B::func2()
A::func3()
~B()
*/

Fun getAddr(void* obj, unsigned int offset)
{
    void* vptr_addr = (void*)*(unsigned long*)obj;
    // 64位操作系统，占8字节，通过*(unsigned long *)obj取出前8字节，即vptr指针
    printf("vptr_addr:%p\n", vptr_addr);

    /**
     * 通过vptr指针访问virtual
     * table，因为虚表中每个元素(虚函数指针)在64位编译器下是8个字节，因此通过*(unsigned
     * long *)vptr_addr取出前8字节， 后面加上偏移量就是每个函数的地址！
     */
    void* func_addr = (void*)*((unsigned long*)vptr_addr + offset);
    printf("func_addr:%p\n", func_addr);
    return (Fun)func_addr;
}
void fun1()
{
    A* a = new A();
    cout << "=======================" << endl;
    Fun f1 = getAddr(a, 0);
    (*f1)();
    cout << "=======================" << endl;
    delete a;
    cout << "=======================" << endl;
    a = new B();
    f1 = getAddr(a, 2);
    (*f1)();
    cout << "=======================" << endl;
    delete a;
}
int main()
{
    fun1();
    cout << "end main" << endl;
    return 0;
}