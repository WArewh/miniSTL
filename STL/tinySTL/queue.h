#ifndef _MYSTL_QUEUE_H
#define _MYSTL_QUEUE_H

#include "deque.h"
#include "functional.h"
#include "vector.h"

namespace mySTL
{
    template <class T, class Container = deque<T>>
    class queue
    {
    public:
        using value_type = typename Container::value_type;
        using reference = typename Container::reference;
        using size_type = typename Container::size_type;

    public:
        bool empty() { return c.empty(); }
        size_type size() { return c.size(); }
        reference front() { return c.front(); }
        reference back() { return c.back(); }

        void push(const T& val) { return c.push_back(val); }
        void pop() { return c.pop_front(); }

    private:
        Container c;
    };
}  // namespace mySTL

namespace mySTL
{
    template <class T, class Container = vector<T>, class Compare = mySTL::less<T>>
    class priority_queue
    {
    public:
        using value_type = typename Container::value_type;
        using reference = typename Container::reference;
        using size_type = typename Container::size_type;

    public:
        priority_queue() : c(), compare() {}

        bool empty() { return c.empty(); }
        size_type size() { return c.size(); }
        reference top() { return c.front(); }

        void push(const T& val);
        void pop();

    private:
        Container c;
        Compare compare;
    };
}  // namespace mySTL

namespace mySTL
{
    template <class T, class Container, class Compare>
    void priority_queue<T, Container, Compare>::push(const T& val)
    {
        c.push_back(val);
        push_heap(c.begin(), c.end(), compare);
    }
    template <class T, class Container, class Compare>
    void priority_queue<T, Container, Compare>::pop()
    {
        pop_heap(c.begin(), c.end(), compare);
        c.pop_back();
    }
}  // namespace mySTL

#endif