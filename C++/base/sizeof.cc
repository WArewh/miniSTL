#include <iostream>
#include <string>
using namespace std;

/*
sizeof看的是占用内存的大小

sizeof(类)
空类的大小为1字节
一个类中，虚函数本身、成员函数（包括静态与非静态）和静态数据成员都是不占用类对象的存储空间。
对于包含虚函数的类，不管有多少个虚函数，只有一个虚指针,vptr的大小。
普通继承，派生类继承了所有基类的函数与成员，要按照字节对齐来计算大小
虚函数继承，不管是单继承还是多继承，都是继承了基类的vptr。
类的数据成员按其声明顺序加入内存，无访问权限无关，只看声明顺序
*/
class A
{
    static int a;
};
class B
{
    char ch[2];
    int a;
    short b[3];
};  // 2+2(对齐)+4+6+2(对齐)=16
class C
{
    short b[3];
    char ch[2];
    int a;
};  // 2+4+6=12
void test()
{
    cout << sizeof(A) << endl;
    cout << sizeof(B) << endl;
    cout << sizeof(C) << endl;
}

class A2
{
    char ch;
    virtual void fun() {}
    virtual void fun1() {}
};
class B2
{
    virtual void fun2() {}
};
class C2 : virtual public A2, virtual public B2
{
public:
    virtual void fun3() {}
};

void test2()
{
    cout << sizeof(A2) << endl;  // 1+8 对齐后16
    cout << sizeof(B2) << endl;
    cout << sizeof(C2) << endl;
}

int main()
{
    test();
    test2();
    return 0;
}