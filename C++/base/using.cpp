#include <iostream>
#include <string>
// 命名空间
using namespace std;

// using可以取代typedef
using String = string;

class Base {
public:
    size_t sizeN() const { return n; }
    size_t sizeM() const { return m; }

protected:
    size_t n;
    size_t m;
};
// 使用了using语句，可以改变他们的可访问性
class Derived : private Base {
public:
    using Base::n;
    using Base::sizeN;
};
void fun1() {
    Derived d;
    cout << d.sizeN() << endl;
    // cout << d.sizeM() << endl;
}

class Base1 {
public:
    void f() { cout << "f()" << endl; }
    void f(int n) { cout << "Base::f(int)" << endl; }
};
// 一条基类成员函数的using声明语句就可以把该函数的所有重载实例添加到派生类的作用域中
class Derived1 : private Base1 {
public:
    using Base1::f;
    void f(int n) { cout << "Derived::f(int)" << endl; }
};

void fun2() {
    Derived1 d1;
    d1.f();
    d1.f(3);
}
int main() {
    fun2();
    return 0;
}