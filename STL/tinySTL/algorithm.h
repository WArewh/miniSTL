#ifndef _MYSTL_ALGORITHM_H
#define _MYSTL_ALGORITHM_H

#include <cstring>

#include "construct.h"
#include "iterator.h"

namespace mySTL
{

    //用value填充[first,last)
    template <class ForwardIterator, class T>
    void fill(ForwardIterator first, ForwardIterator last, const T& value)
    {
        for (; first != last; ++first)
        {
            *first = value;
        }
    }

    //填充N个空间 返回最后一个空间的下一个位置
    template <class OutputIterator, class SizeType, class T>
    OutputIterator fill_n(OutputIterator first, SizeType size, const T& value)
    {
        for (; size > 0; --size, ++first)
        {
            *first = value;
        }
        return first;
    }

    // copy

    template <class InputIterator, class ForwardIterator>
    ForwardIterator _copy_aux(InputIterator first, InputIterator last, ForwardIterator result,
                              has_true_type)
    {
        memmove(result, first, (last - first) * sizeof(*first));
        return result + (last - first);
    }

    template <class InputIterator, class ForwardIterator>
    ForwardIterator _copy_aux(InputIterator first, InputIterator last, ForwardIterator result,
                              has_false_type)
    {
        size_t i;
        for (i = 0; first != last; ++first, ++i)
        {
            mySTL::construct(result + i, *first);
        }
        return (result + i);
    }

    //复制到result并返回result的下一个位置
    template <class InputIterator, class OutputIterator>
    OutputIterator copy(InputIterator first, InputIterator last, OutputIterator result)
    {
        using is_POD =
            typename _type_traits<typename iterator_traits<InputIterator>::value_type>::is_POD_type;
        return _copy_aux(first, last, result, is_POD());
    }

    //距离

    template <class InputIterator>
    inline typename iterator_traits<InputIterator>::difference_type
    _distance_aux(InputIterator first, InputIterator last, input_iterator_tag)
    {
        typename iterator_traits<InputIterator>::difference_type n = 0;
        while (first != last)
        {
            ++first;
            ++n;
        }
        return n;
    }

    template <class InputIterator>
    inline typename iterator_traits<InputIterator>::difference_type
    _distance_aux(InputIterator first, InputIterator last, random_access_iterator_tag)
    {
        return last - first;
    }

    //得到距离
    template <class InputIterator>
    inline typename iterator_traits<InputIterator>::difference_type distance(InputIterator first,
                                                                             InputIterator last)
    {
        return _distance_aux(first, last, iterator_category(first));
    }

    template <class T>
    void swap(T& a, T& b)
    {
        T temp = a;
        a = b;
        b = temp;
    }

    template <class T>
    const T& max(const T& a, const T& b)
    {
        return (a < b) ? b : a;
    }

    template <class T>
    const T& min(const T& a, const T& b)
    {
        return !(b < a) ? a : b;
    }

    // heap

    template <class RandomAccessIterator, class Compare, class Distance, class T>
    void _push_heap(RandomAccessIterator first, Distance hole_index, Distance top_index,
                    const T val, Compare comp)
    {
        Distance parent_index = (hole_index - 1) / 2;
        while (hole_index > top_index && comp(*(first + parent_index), val))
        {
            *(first + hole_index) = *(first + parent_index);
            hole_index = parent_index;
            parent_index = (hole_index - 1) / 2;
        }
        *(first + hole_index) = val;
    }

    template <class RandomAccessIterator, class Compare, class Distance, class T>
    inline void push_heap_aux(RandomAccessIterator first, RandomAccessIterator last, Distance*, T*,
                              Compare comp)
    {
        _push_heap(first, Distance(last - first - 1), Distance(0), T(*(last - 1)), comp);
    }

    template <class RandomAccessIterator, class Compare>
    inline void push_heap(RandomAccessIterator first, RandomAccessIterator last, Compare comp)
    {
        push_heap_aux(first, last, difference_type(first), value_type(first), comp);
    }


    template <class RandomAccessIterator, class Compare, class Distance, class T>
    void _adjust_heap(RandomAccessIterator first, Distance hole_index, Distance len, const T val,
                      Compare comp)
    {
        Distance top_index = hole_index;
        Distance right_index = 2 * (hole_index + 1);  //右孩子
        while (right_index < len)
        {
            if (comp(*(first + right_index), *(first + right_index - 1)))
            {  //选大
                --right_index;
            }
            *(first + hole_index) = *(first + right_index);
            hole_index = right_index;
            right_index = 2 * (hole_index + 1);
        }
        if (right_index == len)
        {  //没有右孩子
            *(first + hole_index) = *(first + right_index - 1);
            hole_index = right_index - 1;
        }
        _push_heap(first, hole_index, top_index, val, comp);
    }

    template <class RandomAccessIterator, class Compare, class Distance, class T>
    void _pop_heap(RandomAccessIterator first, RandomAccessIterator last,
                   RandomAccessIterator result, const T val, Distance*, Compare comp)
    {
        *result = *first;
        _adjust_heap(first, Distance(0), Distance(last - first), val, comp);
    }

    template <class RandomAccessIterator, class Compare, class T>
    inline void pop_heap_aux(RandomAccessIterator first, RandomAccessIterator last, T*,
                             Compare comp)
    {
        _pop_heap(first, last - 1, last - 1, T(*(last - 1)), difference_type(first), comp);
    }

    template <class RandomAccessIterator, class Compare>
    inline void pop_heap(RandomAccessIterator first, RandomAccessIterator last, Compare comp)
    {
        pop_heap_aux(first, last, value_type(first), comp);
    }

    template <class RandomAccessIterator, class Compare>
    void sort_heap(RandomAccessIterator first, RandomAccessIterator last, Compare comp)
    {
        while (last - first > 1)
        {
            pop_heap(first, last--, comp);
        }
    }

    template <class RandomAccessIterator, class Compare, class Distance, class T>
    void _make_heap(RandomAccessIterator first, RandomAccessIterator last, T*, Distance*,
                    Compare comp)
    {
        Distance len = last - first;
        if (len < 2)
            return;

        Distance index = (len - 2) / 2;  //第一个需要重排的子树头部
        while (index >= 0)
        {
            _adjust_heap(first, index, len, *(first + index), comp);
            --index;
        }
    }

    template <class RandomAccessIterator, class Compare>
    inline void make_heap(RandomAccessIterator first, RandomAccessIterator last, Compare comp)
    {
        _make_heap(first, last, value_type(first), difference_type(first), comp);
    }

}  // namespace mySTL

#endif