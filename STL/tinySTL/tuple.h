#ifndef _MYSTL_TUPLE_H
#define _MYSTL_TUPLE_H

#include "algorithm.h"

namespace mySTL
{

    template <typename... Type>
    struct tuple;

    template <>
    struct tuple<>
    {
    };

    using null_tuple = tuple<>;

    template <typename T, typename... Types>
    struct tuple<T, Types...> : public tuple<Types...>
    {
        using value_type = T;
        using base_type = tuple<Types...>;
        using this_type = tuple<T, Types...>;

        tuple(value_type val, Types... base) : base_type(base...), value(val) {}

        const T& head() const { return value; }
        T& head() { return value; }

    protected:
        value_type value;
    };

    template <typename T>
    struct tuple<T> : public null_tuple
    {
        using value_type = T;
        using base_type = null_tuple;
        using this_type = tuple<T>;

        tuple(T val) : value(val) {}

        const T& head() const { return value; }
        T& head() { return value; }

    protected:
        value_type value;
    };

    template <unsigned N, typename... Types>
    struct tuple_impl;

    template <unsigned int N, typename T, typename... Types>
    struct tuple_impl<N, tuple<T, Types...>>
    {
        typedef typename tuple_impl<N - 1, tuple<Types...>>::value_type value_type;
        typedef typename tuple_impl<N - 1, tuple<Types...>>::tuple_type tuple_type;
    };

    template <typename T, typename... Types>
    struct tuple_impl<0, tuple<T, Types...>>
    {
        using value_type = T;
        using tuple_type = tuple<T, Types...>;
    };

    template <>
    struct tuple_impl<0, null_tuple>
    {
        using value_type = null_tuple;
        using tuple_type = null_tuple;
    };

    template <unsigned int N, typename... Types>
    constexpr const typename tuple_impl<N, tuple<Types...>>::value_type&
    tuple_get(const tuple<Types...>& tuple_)
    {
        typedef tuple<Types...> tuple_type;
        typedef typename tuple_impl<N, tuple_type>::tuple_type base_tuple_type;

        return static_cast<const base_tuple_type&>(tuple_).head();
    }

    template <unsigned int N, typename... Types>
    typename tuple_impl<N, tuple<Types...>>::value_type& tuple_get(tuple<Types...>& tuple_)
    {
        typedef tuple<Types...> tuple_type;
        typedef typename tuple_impl<N, tuple_type>::tuple_type base_tuple_type;

        return static_cast<base_tuple_type&>(tuple_).head();
    }

}  // namespace mySTL

#endif