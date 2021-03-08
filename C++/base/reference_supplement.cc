#include <algorithm>
#include <iostream>
#include <string>
using namespace std;

class Person
{
public:
    explicit Person(const Person& p) {}
    // template <typename T>
    // explicit Person(T&& n)  // 完美转发构造函数，本意是最快速度构造、少写代码
    //     : name(std::forward<T>(n))
    // {
    // }
    //解决办法一
    //去掉万能引用方法，实现复制构造和移动构造

    // 解决办法二
    // 添加一个优先级比万能引用高的
    // explicit Person(Person& p) {}

    // 解决办法三
    // 标签派发
    // 如果是person子类返回void 不是则返回T
    template <typename T, typename = enable_if_t<!is_base_of<Person, decay_t<T>>::value>>
    explicit Person(T&& n) : name(std::forward<T>(n))
    {
    }

    std::string name;
};

int main()
{
    Person p1("wang");
    // 会使用万能引用，因为传入的是Person需要转换，而万能引用不需要转换
    Person p2(p1);
    return 0;
}