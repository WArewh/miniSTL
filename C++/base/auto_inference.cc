#include <iostream>
#include <string>
using namespace std;

/*
auto推导
基本同模板的T推导 会去掉vonst volatic修饰
*/

void f1()
{
    const int v = 0;
    auto var = v;             // int
    auto ptr = &var;          // int*
    const auto cvar = var;    // const int
    const auto& crvar = var;  // const int&
    auto* pvar = &cvar;       // const int*

    auto&& ref = var;    // int&
    auto&& cref = cvar;  // const int&
    auto&& rref = 0;     // int&&

    const char name[] = "abc";
    auto arr1 = name;   // const char*
    auto& arr2 = name;  // const char[&][4]
}
/*
auto特例 {}
*/
void f2()
{
    auto x1 = {0};  // std::initializer_list<int>
}

int main()
{
    return 0;
}