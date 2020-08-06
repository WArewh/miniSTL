#ifndef _MYSTL_FUNCTIONAL_H
#define _MYSTL_FUNCTIONAL_H

#include "utility.h"

namespace mySTL {


    template <class Arg, class Result>
    struct unary_function {
        using argument_type = Arg;
        using result_type = Result;
    };

    template <class Arg1, class Arg2, class Result>
    struct binary_function {
        using first_argument_type = Arg1;
        using second_argument_type = Arg2;
        using result_type = Result;
    };

    template <class T>
    struct plus : public binary_function<T, T, T> {
        T operator()(const T& x, const T& y) { return x + y; }
    };

    template <class T>
    struct less : public binary_function<T, T, bool> {
        bool operator()(const T& x, const T& y) { return x < y; }
    };

    template <class T>
    struct greater : public binary_function<T, T, bool> {
        bool operator()(const T& x, const T& y) { return x > y; }
    };

    template <class T>
    struct equal_to : public binary_function<T, T, T> {
        T operator()(const T& x, const T& y) { return x == y; }
    };

    template <class T>
    struct identity : public unary_function<T, T> {
        const T& operator()(const T& x) { return x; }
    };

    template <class Pair>
    struct select1st : public unary_function<Pair, typename Pair::first_type> {
        typename Pair::first_type operator()(const Pair& x) const { return x.first; }
    };

    template <class Pair>
    struct select2nd : public unary_function<Pair, typename Pair::second_type> {
        typename Pair::first_type operator()(const Pair& x) const { return x.second; }
    };

}  // namespace mySTL

#endif