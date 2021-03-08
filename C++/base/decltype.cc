#include <iostream>
#include <string>
#include <vector>
using namespace std;

/*
decltype(name)含义为得到name的确切类型
*/
void f1()
{
    auto v = 3;
    auto& rv = v;
    auto* pv = &v;
    const auto cv = v;
    decltype(v) d = v;
    decltype(rv) rd = v;
    decltype(pv) pd = &v;
    decltype(cv) cd = v;
}
// decltype特例 vector<bool>
void f2()
{
    int v = 3;
    vector<int> vec_int;
    vector<bool> vec_bool;
    decltype(vec_int[0]) var = v;  // int&
    decltype(vec_bool[0]) flag;    // std::vector<bool>::reference
}

/*
    decltype经常和auto一起使用，只用auto会导致类型退化
    比如：int&的auto推导为int

    使用万能引用这样就可以接受左值和右值，并且使用std::forward进行完美转发
*/
// c++14
template <typename Container, typename Index>
decltype(auto) getVar1(Container&& c, Index i)
{
    return std::forward<Container>(c)[i];
}

// c++11
template <typename Container, typename Index>
auto getVar2(Container&& c, Index i) -> decltype(std::forward<Container>(c)[i])
{
    return std::forward<Container>(c)[i];
}

// 注意(x)的类型为引用，因此decltype会返回引用
decltype(auto) fun1()
{
    int x;
    return x;
}
decltype(auto) fun2()
{
    int x;
    return (x);  // 不要返回局部引用！
}
void f3()
{
    fun1();
    fun2();
}


int main()
{
}