#include <iostream>
#include <memory>
#include <vector>
using namespace std;

// smart_ptr补充

void f1()
{
}

void f2()
{
    auto p1 = make_shared<int>(5);           // 分配一次内存
    auto p2 = make_shared<int>(new int(5));  // 分配两次内存

    auto p3 = make_shared<vector<int>>(10, 20);
    // auto p4 = make_shared<vector<int>>({10, 20});  // 不接受
    cout << p3->size() << endl;  // 10
}

void f3()
{
}

int main()
{
    f2();
}