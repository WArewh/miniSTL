#include <iostream>
#include <string>
using namespace std;

/*

RTTI通过运行时类型信息程序能够使用基类的指针或引用来检查这些指针或引用所指的对象的实际派生类型。
在面向对象程序设计中，有时我们需要在运行时查询一个对象是否能作为某种多态类型使用。
Java的instanceof，以及C#的as、is运算符类似，C++提供了dynamic_cast函数用于动态转型。
dynamic_cast提供了类型安全检查，所以在多态类型间进行转换更提倡采用dynamic_cast。

*/
class A {
    virtual void fun() {}
};

class B {
    virtual void fun() {}
};

class D : public B {};

int main() {
    B* b = new D; // 向上转型
    B& obj = *b;
    D* d = dynamic_cast<D*>(b); // 向下转型
    if (d != NULL)
        cout << "works" << endl;
    else
        cout << "cannot cast B* to D*";
    try {
        D& dobj = dynamic_cast<D&>(obj);
        cout << "works" << endl;
    } catch (bad_cast bc) { // ERROR
        cout << bc.what() << endl;
    }
    return 0;
}
