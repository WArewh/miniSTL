#include <iostream>
#include <string>
using namespace std;
/*

类内定义即为隐式inline
类外定义需要显式inline

编译器对 inline 函数的处理步骤
将 inline 函数体复制到 inline 函数调用点处；
为所用 inline 函数中的局部变量分配内存空间；
将 inline 函数的的输入参数和返回值映射到调用方法的局部变量空间中；
如果 inline 函数有多个返回点，将其转变为 inline 函数代码块末尾的分支（使用
GOTO）。

虚函数可以是内联函数，内联是可以修饰虚函数的，但是当虚函数表现多态性的时候不能内联。
内联是在编译期间建议编译器内联，而虚函数的多态性在运行期
编译器无法知道运行期调用哪个代码，因此虚函数表现为多态性时（运行期）不可以内联。
*/

class Base {
public:
    inline virtual void who() { cout << "I am Base\n"; }
    virtual ~Base() {}
};
class Derived : public Base {
public:
    inline virtual void who() // 不写inline也是内联
    {
        cout << "I am Derived\n";
    }
};

int main() {
    // 此处的虚函数who()编译期间就能确定了，所以它可以是内联的，但最终是否内联取决于编译器。
    Base b;
    b.who();

    // 此处的虚函数是通过指针调用的，呈现多态性，需要在运行时期间才能确定，所以不能内联。
    Base* ptr = new Derived();
    ptr->who();

    // 因为Base有虚析构函数（virtual ~Base() {}），
    // delete时，会先调用派生类析构函数，再调用基类析构函数，防止内存泄漏。
    delete ptr;
    ptr = nullptr;

    return 0;
}