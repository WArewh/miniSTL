#include <iostream>
#include <string>
using namespace std;
/*

纯虚函数：没有函数体的虚函数,通过声明中赋值0来声明纯虚函数
抽象类：包含纯虚函数的类
抽象类只能作为基类来派生新类使用，不能创建抽象类的对象
如果一个类从抽象类派生而来，它必须实现了基类中的所有纯虚函数，才能成为非抽象类。

构造函数不能是虚函数，而析构函数可以是虚析构函数
当基类指针指向派生类对象并删除对象时，我们可能希望调用适当的析构函数。
如果析构函数不是虚拟的，则只能调用基类析构函数。
*/

/*

构造函数不可以声明为虚函数。同时除了inline或explicit之外，构造函数不允许使用其它任何关键字。
尽管虚函数表vtable是在编译阶段就已经建立的，
但指向虚函数表的指针vptr是在运行阶段实例化对象时才产生的。
如果类含有虚函数，编译器会在构造函数中添加代码来创建vptr。
问题来了，如果构造函数是虚的，那么它需要vptr来访问vtable，可这个时候vptr还没产生。
因此，构造函数不可以为虚函数。
我们之所以使用虚函数，是因为需要在信息不全的情况下进行多态运行。
而构造函数是用来初始化实例的，实例的类型必须是明确的。
因此，构造函数没有必要被声明为虚函数。

*/

/*

通常类成员函数都会被编译器考虑是否进行内联。
但通过基类指针或者引用调用的虚函数必定不能被内联，因为内联是在编译期的时候进行的。
当然，实体对象调用虚函数或者静态调用时可以被内联，虚析构函数的静态调用也会被内联展开。

*/

class A
{
    int a;

public:
    A(int a) : a(a) {}
    virtual ~A() { cout << "~A()" << endl; }
    virtual void show() = 0;
    virtual void display() = 0;
};

class B : public A
{
public:
    B(int a) : A(a) {}
    virtual ~B() { cout << "~B()" << endl; }
    virtual void show() { cout << "show()" << endl; }
    virtual void display() { cout << "display()" << endl; }
};

void fun1()
{
    // A a; error
    A* p_a = new B(3);
    p_a->show();
    delete p_a;
}

int main()
{
    fun1();
    return 0;
}