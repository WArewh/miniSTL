#include <iostream>
#include <string>
using namespace std;
class A
{
public:
    A() {}
    A(int i) { cout << "A::int" << endl; }
    A(initializer_list<long> list) { cout << "A::list" << endl; }
    ~A() {}
};

class B
{
public:
    B() {}
    B(int i) { cout << "B::int" << endl; }
    B(initializer_list<short> list) { cout << "B::list" << endl; }
    ~B() {}
};

class C
{
public:
    C() {}
    C(int i) { cout << "C::int" << endl; }
    C(initializer_list<string> list) { cout << "C::list" << endl; }
    ~C() {}
};

class D
{
public:
    D() {}
    D(int i) { cout << "D::int" << endl; }
    D(initializer_list<short> list) { cout << "D::list" << endl; }
    ~D() {}
    operator char() const
    {
        cout << "D::transform" << endl;
        return 0;
    }
};

/*
初始化列表(大括号构造法)
特性:
    1.禁止内建类型进行窄化，但可以宽化 f1()
    2.C++规定能解析为声明的都要解析为声明，而大括号可以解决此问题 f2()
    3.如果对象有initializer_list<type>构造函数，只要可以推导出type或type窄化
    就会优先使用initializer_list<type> f3()
    4.如果有多个initializer_list<type>构造函数，会选取当前最合适的构造函数
    如果在后面添加了其他initializer_list<type>构造函数，则要小心以前的构造函数被覆盖的可能性
*/
void f1()
{
    float f = 0.0;
    // int v1{f};
    int v2(f);
    double v3{f};
}

void f2()
{
    // A a1();// 创建一个对象，却被认为是一个函数
    A a2{};
}

void f3()
{
    int x = 0;
    A a1{x};  // A::list
    // B b1{x};  // invalid narrowing conversion from "int" to "short"
    C c1{x};   // C::int
    D d1{};    // D()
    D d2{d1};  // 转为char类型，再接受initializer_list<short>
    A a2{{}};  // A::list 空的initializer_list
}

int main()
{
    f3();
    return 0;
}