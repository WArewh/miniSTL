#ifndef _MYSTL_FUNCTIONAL_H
#define _MYSTL_FUNCTIONAL_H

namespace mySTL {

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

}  // namespace mySTL

#endif