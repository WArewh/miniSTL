#include <iostream>
#include <string>
using namespace std;

// decltype的作用是“查询表达式的类型”

// 定义类型或者推导出表达式类型
using size_t = decltype(sizeof(0));
// 泛型编程中结合auto，用于追踪函数的返回值类型
template <typename T> auto add(T& x, T& y) -> decltype(x * y) { return x * y; }
void fun1() {
    int a = 1, b = 2;
    auto c = add(a, b);
}

int&& ret();
int bar(char);
int bar(int);

void fun2() {
    // e是一个没有带括号的标记符表达式或者类成员访问表达式
    // 那么的decltype(e)就是e所命名的实体的类型。
    int a = 1;
    int& r = a;
    int* p = &a;
    decltype(a) var1 = 2;
    decltype(r) var2 = var1;
    decltype(p) var3 = &var1;

    // 假设e的类型是T，如果e是一个左值，那么decltype(e)为T&。
    // 假设e的类型是T，则decltype(e)为T
    int arr[4] = {0};
    decltype(arr) _arr = {0};//int[4]
    decltype(arr[3]) r1 = a;//int&
    decltype(arr[3] + 1) var = 3;//int
    decltype(++a)temp_val1=a;//int&

    // 假设e的类型是T，如果e是一个将亡值，那么decltype(e)为T&&
    decltype(ret())r_val=3;//int&&
    decltype(a++)temp_val2=a;//int why?
}

int main() {
    fun2();
    return 0;
}