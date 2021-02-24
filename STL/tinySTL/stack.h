#ifndef _MYSTL_STACK_H
#define _MYSTL_STACK_H

#include "deque.h"

namespace mySTL
{
    template <class T, class Container = deque<T>>
    class stack
    {
    public:
        using value_type = typename Container::value_type;
        using reference = typename Container::reference;
        using size_type = typename Container::size_type;

    public:
        bool empty() { return c.empty(); }
        size_type size() { return c.size(); }
        reference top() { return c.back(); }

        void push(const T& val) { return c.push_back(val); }
        void pop() { return c.pop_back(); }

    private:
        Container c;
    };
}  // namespace mySTL


#endif