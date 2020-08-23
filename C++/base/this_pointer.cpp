#include <iostream>
#include <string>
using namespace std;

/*
this指针是一个指针常量A*右值

this指针的使用：
在类的非静态成员函数中返回类对象本身的时候，直接使用 return *this。
当参数与成员变量名相同时，如this->n = n （不能写成n = n)。

*/
class people {
private:
    const char sex;
    string name;

public:
    people(char sex, string name) : sex(sex) { this->name = name; }
    string getName() const { return this->name; }
    char getSex() const { return sex; }
    void printInfo() const { cout << sex << " " << name << endl; }
};
void test1() {
    people p1('m', "zhangsan");
    p1.printInfo();
    const people p2('w', "wangermazi");
    cout << p1.getSex() << " " << p1.getName() << endl;
    cout << p2.getSex() << " " << p2.getName() << endl;
}
int main() {
    test1();
    return 0;
}