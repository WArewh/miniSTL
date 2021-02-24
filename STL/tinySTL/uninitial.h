#ifndef _MYSTL_UNINITIALIZED_H
#define _MYSTL_UNINITIALIZED_H

#include <cstring>

#include "algorithm.h"
#include "construct.h"
#include "iterator.h"
#include "typeTraits.h"

namespace mySTL
{

    // uninitialized_copy
    template <class InputIterator, class ForwardIterator>
    ForwardIterator _uninitialized_copy_aux(InputIterator first, InputIterator last,
                                            ForwardIterator result, has_true_type)
    {
        memmove(result, first, (last - first) * sizeof(*first));
        return result + (last - first);
    }

    template <class InputIterator, class ForwardIterator>
    ForwardIterator _uninitialized_copy_aux(InputIterator first, InputIterator last,
                                            ForwardIterator result, has_false_type)
    {
        size_t i;
        for (i = 0; first != last; ++first, ++i)
        {
            mySTL::construct(result + i, *first);
        }
        return (result + i);
    }

    template <class InputIterator, class ForwardIterator>
    ForwardIterator uninitialized_copy(InputIterator first, InputIterator last,
                                       ForwardIterator result)
    {
        using is_POD =
            typename _type_traits<typename iterator_traits<InputIterator>::value_type>::is_POD_type;
        return _uninitialized_copy_aux(first, last, result, is_POD());
    }

    // uninitialized_fill
    template <class ForwardIterator, class T>
    void _uninitialized_fill_aux(ForwardIterator first, ForwardIterator last, const T& value,
                                 has_true_type)
    {
        mySTL::fill(first, last, value);
    }
    template <class ForwardIterator, class T>
    void _uninitialized_fill_aux(ForwardIterator first, ForwardIterator last, const T& value,
                                 has_false_type)
    {
        for (; first != last; ++first)
        {
            mySTL::construct(first, value);
        }
    }

    template <class ForwardIterator, class T>
    void uninitialized_fill(ForwardIterator first, ForwardIterator last, const T& value)
    {
        using is_POD = typename _type_traits<T>::is_POD_type;
        _uninitialized_fill_aux(first, last, value, is_POD());
    }

    // uninitialized_fill_n
    template <class ForwardIterator, class SizeType, class T>
    inline ForwardIterator _uninitialized_fill_n_aux(ForwardIterator first, SizeType size,
                                                     const T& x, has_true_type)
    {
        return mySTL::fill_n(first, size, x);
    }

    template <class ForwardIterator, class SizeType, class T>
    inline ForwardIterator _uninitialized_fill_n_aux(ForwardIterator first, SizeType size,
                                                     const T& x, has_false_type)
    {
        for (; size > 0; --size, ++first)
        {
            mySTL::construct(first, x);
        }
        return first;
    }

    template <class ForwardIterator, class SizeType, class T>
    inline ForwardIterator uninitialized_fill_n(ForwardIterator first, SizeType size, const T& x)
    {
        using is_POD = typename _type_traits<T>::is_POD_type;
        return _uninitialized_fill_n_aux(first, size, x, is_POD());
    }

}  // namespace mySTL

#endif