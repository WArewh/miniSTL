#include <functional>
#include <iostream>
#include <map>
#include <string>
#include <vector>
using namespace std;

/*
优先选用auto,而不是显式类型声明
使用auto可以简化类型声明，而且还会提醒自己初始化以及避免很多错误　f1() f2() f3()
只有使用auto推导出不是想要的类型，才使用带显示类型的初始化 f4()
*/

void f1()
{
    vector<int> v;

    vector<int>::const_iterator it1 = v.cbegin();  // 不使用auto
    auto it2 = v.cbegin();                         // 使用auto简化类型声明

    int size1 = v.size();   // 不使用auto可能会导致返回类型和声明类型不一致
    auto size2 = v.size();  // 使用auto避免和函数返回类型不同
}

void f2()
{
    map<string, int> mp;

    for (const auto& p2 : mp)  // p2的类型为const pair<const string, int>
    {
    }

    // 会有严重的性能问题
    for (const pair<string, int>& p1 : mp)  // p1的类型为const pair<string, int>　
    {
        // 每次循环都会先将mp中的对象进行复制
        // 得到临时变量const pair<string, int>tmp
        // p1=tmp
        // 执行完操作，tmp析构
    }
}

void f3()
{
    auto fun1 = [](const int& x, const int& y) { return x < y; };  // 简化声明类型，减少内存开销
    function<bool(const int& x, const int& y)> fun2 = [](const int& x, const int& y) {
        return x < y;
    };  // 使用function，持有一个实例

    cout << sizeof(fun1) << endl;  // 1
    cout << sizeof(fun2) << endl;  // 32
}

void f4()
{
    vector<bool> vec{true};
    auto t1 = vec[0];  // t的类型为vector<bool>::reference 实际想要bool

    // 这个问题出现是因为在vector<bool>实现使用了”隐形“的代理类,因此出现了问题

    // 解决办法如下
    auto t2 = static_cast<bool>(vec[0]);
}


int main()
{
    f3();
}