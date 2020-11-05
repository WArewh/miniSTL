#include <iostream>
#include <string>
using namespace std;
/*
枚举常量不会占用对象的存储空间，它们在编译时被全部求值。

传统的enum
作用域不受限,会容易引起命名冲突。
会隐式转换为int
用来表征枚举变量的实际类型不能明确指定，从而无法支持枚举类型的前向声明。

*/

// enum Feeling;
enum Color { RED, BLUE };
// enum Feeling {EXCITED,BLUE};

// "有效"的办法是用一个类或结构体来限定其作用域
struct Color1 {
    enum Type { RED, YELLOW, BLUE };
};

// C++11 枚举 可以指定类型同时限定作用域
enum class Color2 : uint8_t { RED, YELLOW, BLUE };

int main() { return 0; }