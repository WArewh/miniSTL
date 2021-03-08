#include <iostream>
#include <string>
using namespace std;

/*
    const的主要用途为常量，防止修改起到保护作用，需要初始化。

    const常量具有类型，编译器可以进行安全检查；
    #define宏定义没有数据类型，只是简单的字符串替换，不能进行安全检查

    const定义常量从汇编的角度来看，只是给出了对应的内存地址，而不是像#define一样给出的是立即数
    所以，const定义的常量在程序运行过程中只有一份拷贝，而#define定义的常量在内存中有若干个拷贝。

*/

/*
    指针与const
    (int*)const         指针是个常量不能改变指向
    (const int)*        指向的值为常量
    ((const int)*)const 指向和指向的值都不可改变
*/
void test1()
{
    int a = 5, b = 10;
    int* const c1 = &a;
    const int* c2 = &a;
    const int* const c3 = &a;
    // c1=&b; error
    c2 = &b;
    *c1 = 10;
    // *c2=10; error
    cout << "*c1=" << *c1 << endl;
    cout << "*c2=" << *c2 << endl;
    cout << "*c3=" << *c3 << endl;
}

/*
    const对象只能访问const成员函数,而非const对象可以访问任意的成员函数,包括const成员函数
*/

class people
{
private:
    const char sex = 'm';  // c++11
    string name = "wang";

public:
    people(){};
    people(char sex, string name) : sex(sex), name(name) {}
    string getName() const { return name; }
    char getSex() const { return sex; }
    void printInfo() { cout << sex << " " << name << endl; }
};

void test2()
{
    people p;

    people p1('m', "zhangsan");
    const people p2('w', "wangermazi");
    cout << p.getSex() << " " << p.getName() << endl;
    cout << p1.getSex() << " " << p1.getName() << endl;
    cout << p2.getSex() << " " << p2.getName() << endl;
    p1.printInfo();
    // p2.printInfo(); error
}

int main()
{
    test2();
    return 0;
}