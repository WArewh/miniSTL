#include <iostream>
#include <string>
using namespace std;

/*
模板参数为T，含义为得到T的副本:
因此有引用、const、volatile修饰都去掉
*/
template <typename T>
void f(T t);

void fun()
{
    int integer = 0;
    int& ref_integer = integer;
    int* ptr_integer = &integer;
    const int cinteger = integer;
    const int* cptr_integer = &integer;
    const int* const cptrc_integer = &integer;

    f(integer);        // int
    f(ref_integer);    // int
    f(ptr_integer);    // int*
    f(cinteger);       // int
    f(cptr_integer);   // (const int)* 指向常量的指针 指针上没有修饰
    f(cptrc_integer);  // (const int)*

    char str1[] = "abcd";
    const char str2[] = "abcd";
    f(str1);  // char*
    f(str2);  // const char*
}

/*
模板参数为T&，含义为得到T的引用:
去掉引用，得到T，传入参数没有引用也不会报错
再加上引用
*/
template <typename T>
void f1(T& t);

void fun1()
{
    int integer = 0;
    int& ref_integer = integer;
    int* ptr_integer = &integer;
    const int cinteger = integer;
    const int* cptr_integer = &integer;
    const int* const cptrc_integer = &integer;

    f1(integer);        // int&
    f1(ref_integer);    // int&
    f1(ptr_integer);    // int*&
    f1(cinteger);       // const int&
    f1(cptr_integer);   // const int*&
    f1(cptrc_integer);  // const int* const&

    char str1[] = "abcd";
    const char str2[] = "abcd";
    f1(str1);  // char (&)[5]
    f1(str2);  // const char(&)[5]
}

/*
模板参数为T&，含义为得到T的指针:
去掉指针，得到T，如果没有传入参数没有指针则报错
再加上指针
*/
template <typename T>
void f2(T* t);

void fun2()
{
    int integer = 0;
    int& ref_integer = integer;
    int* ptr_integer = &integer;
    const int cinteger = integer;
    const int* cptr_integer = &integer;
    const int* const cptrc_integer = &integer;

    // f2(integer);
    // f2(ref_integer);
    f2(ptr_integer);  // int*
    // f2(cinteger)
    f2(cptr_integer);   // const int*
    f2(cptrc_integer);  // const int*

    char str1[] = "abcd";
    const char str2[] = "abcd";
    f2(str1);  // char*
    f2(str2);  // const char*
}

/*
模板参数为T&&(万能引用)，含义为得到传入参数的引用:
直接加上引用，引用的引用还是引用
*/
template <typename T>
void f3(T&& t);
void fun3()
{
    int integer = 0;
    int& ref_integer = integer;
    int* ptr_integer = &integer;
    const int cinteger = integer;
    const int* cptr_integer = &integer;
    const int* const cptrc_integer = &integer;

    f3(integer);        // int&
    f3(ref_integer);    // int&
    f3(ptr_integer);    // int*&
    f3(cinteger);       // const int&
    f3(cptr_integer);   // const int*&
    f3(cptrc_integer);  // const int* const&
    f3(0);              // int&&

    char str1[] = "abcd";
    const char str2[] = "abcd";
    f3(str1);  // char (&)[5]
    f3(str2);  // const char(&)[5]
}

int main()
{
    return 0;
}