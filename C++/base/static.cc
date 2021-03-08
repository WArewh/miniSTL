#include <iostream>
#include <string>
using namespace std;
/*
当变量声明为static时，这个变量持续到程序的生命周期结束。
即使多次调用该函数，静态变量的空间也只分配一次，前一次调用中的变量值会保留下来。
*/

void test1()
{
    static int count = 0;
    count++;
    cout << count << endl;
}

/*

类中的静态变量由对象共享。也是因为这个原因，静态变量不能使用构造函数初始化,但可以更改
静态成员函数也不依赖于类的对象。
我们可以使用对象和'.'来调用静态成员函数。但建议使用类名和范围解析运算符调用静态成员

*/
class people
{
private:
    const char sex;
    string name;
    static int count;

public:
    static const int count_hands = 2;  // C++11

    people(char sex, string name) : sex(sex), name(name)
    {
        count++;
        cout << "create" << endl;
    }
    ~people()
    {
        count--;
        cout << "destory" << endl;
    }
    char getSex() const { return sex; }
    static int getCount() { return count; }
};

int people::count = 0;

void test2()
{
    people p1('m', "zhangsan");
    static people p2('w', "wangermazi");
    cout << "当前人数为" << p1.getCount() << endl;
    cout << "当前人数为" << people::getCount() << endl;  //推荐
}

/*
在类外使用static，类似c的static，
只能在声明它的文件中可见，其他文件不能引用该函数
不同的文件可以使用相同名字的静态函数，互不影响
*/

int main()
{
    for (int i = 0; i < 5; i++)
    {
        test1();
    }
    test2();
    cout << "main end" << endl;
    return 0;
}