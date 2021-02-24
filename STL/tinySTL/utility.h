#ifndef _MYSTL_UTILITY_H
#define _MYSTL_UTILITY_H

#include "algorithm.h"

namespace mySTL
{
    template <class T1, class T2>

    struct pair
    {
    public:
        using first_type = T1;
        using second_type = T2;
        first_type first;
        second_type second;

    public:
        pair() {}
        pair(const T1& a, const T2& b) : first(a), second(b) {}
        pair& operator=(const pair& pr);
    };

}  // namespace mySTL


namespace mySTL
{

    template <class T1, class T2>
    pair<T1, T2>& pair<T1, T2>::operator=(const pair<T1, T2>& pr)
    {
        first = pr.first;
        second = pr.second;
        return *this;
    }

    //逻辑比较
    template <class T1, class T2>
    bool operator==(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
    {
        return lhs.first == rhs.first && lhs.second == rhs.second;
    }

    template <class T1, class T2>
    bool operator!=(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
    {
        return !(lhs == rhs);
    }



    template <class U, class V>
    pair<U, V> make_pair(const U& u, const V& v)
    {
        return pair<U, V>(u, v);
    }

}  // namespace mySTL

#endif