#include <iostream>
using namespace std;
class Base {
public:
    virtual void fun(int x = 10) { cout << "Base::fun(), x = " << x << endl; }
};

class Derived : public Base {
public:
    virtual void fun(int x = 20) {
        cout << "Derived::fun(), x = " << x << endl;
    }
};

// 虚函数的调用取决于指向或者引用的对象的类型，而不是指针或者引用自身的类型

// 默认参数是静态绑定的。默认参数的使用需要看指针或者应用本身的类型
void fun1() {
    Derived d1;
    Base* bp = &d1;
    bp->fun(); // 10
}

/*

静态函数不可以声明为虚函数，同时也不能被const 和 volatile关键字修饰
static成员函数不属于任何类对象或类实例，所以即使给此函数加上virutal也是没有任何意义
虚函数依靠vptr和vtable来处理。
vptr是一个指针，在类的构造函数中创建生成只能用this指针来访问它
静态成员函数没有this指针，所以无法访问vptr。

*/

int main() {
    fun1();
    return 0;
}

