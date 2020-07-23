#ifndef _MYSTL_ALGORITHM_H
#define _MYSTL_ALGORITHM_H

#include <cstring>

#include "construct.h"
#include "iterator.h"

namespace mySTL {

    //用value填充[first,last)
    template <class ForwardIterator, class T>
    void fill(ForwardIterator first, ForwardIterator last, const T& value) {
        for (; first != last; ++first) {
            *first = value;
        }
    }

    //填充N个空间 返回最后一个空间的下一个位置
    template <class OutputIterator, class SizeType, class T>
    OutputIterator fill_n(OutputIterator first, SizeType size, const T& value) {
        for (; size > 0; --size, ++first) {
            *first = value;
        }
        return first;
    }

    // copy

    template <class InputIterator, class ForwardIterator>
    ForwardIterator _copy_aux(InputIterator first, InputIterator last, ForwardIterator result,
                              _true_type) {
        memmove(result, first, (last - first) * sizeof(*first));
        return result + (last - first);
    }

    template <class InputIterator, class ForwardIterator>
    ForwardIterator _copy_aux(InputIterator first, InputIterator last, ForwardIterator result,
                              _false_type) {
        size_t i;
        for (i = 0; first != last; ++first, ++i) {
            mySTL::construct(result + i, *first);
        }
        return (result + i);
    }

    //复制到result并返回result的下一个位置
    template <class InputIterator, class OutputIterator>
    OutputIterator copy(InputIterator first, InputIterator last, OutputIterator result) {
        using is_POD =
            typename _type_traits<typename iterator_traits<InputIterator>::value_type>::is_POD_type;
        return _copy_aux(first, last, result, is_POD());
    }

    //距离

    template <class InputIterator>
    inline typename iterator_traits<InputIterator>::difference_type
    _distance_aux(InputIterator first, InputIterator last, input_iterator_tag) {
        typename iterator_traits<InputIterator>::difference_type n = 0;
        while (first != last) {
            ++first;
            ++n;
        }
        return n;
    }

    template <class InputIterator>
    inline typename iterator_traits<InputIterator>::difference_type
    _distance_aux(InputIterator first, InputIterator last, random_access_iterator_tag) {
        return last - first;
    }

    //得到距离
    template <class InputIterator>
    inline typename iterator_traits<InputIterator>::difference_type distance(InputIterator first,
                                                                             InputIterator last) {
        return _distance_aux(first, last, iterator_category(first));
    }

    template <class T>
    void swap(const T& a, const T& b) {
        T temp = a;
        a = b;
        b = temp;
    }

    template <class T>
    const T& max(const T& a, const T& b) {
        return (a < b) ? b : a;
    }

    template <class T>
    const T& min(const T& a, const T& b) {
        return !(b < a) ? a : b;
    }
}  // namespace mySTL

#endif