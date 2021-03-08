#include <functional>
#include <iostream>
using namespace std;

class A
{
public:
    static const int a = 0;
};

template <typename T>
void fun(T&& t)
{
}

void set(int a)
{
}
void set(int a, int b)
{
}

struct BitDomain
{
    uint32_t v1 : 4, v2 : 8, v3 : 20;
};

void question()
{
    // case 1
    // fun({1, 2, 3});  //大括号初始化

    // case 2
    // fun(NULL);       // 类型错误

    // case 3
    // fun(A::a);       // 只有声明，使用到的地方会变成常量，常量取不到地址

    // case 4
    // fun(set);  // 重载不知道调用那个

    // case 5
    // BitDomain d;
    // fun(d.v2);  //不能明确指向
}

//// case 3
const int A::a;  //定义

void solution()
{

    // case 1
    auto list = {1, 2, 3};
    fun(list);

    // case 2
    fun(nullptr);

    // case 3
    fun(A::a);

    // case 4
    function<void(int)> func = bind((void (*)(int)) & set, placeholders::_1);


    // case 5
    BitDomain d;
    auto v = d.v2;
    fun(v);
}

int main()
{
    return 0;
}