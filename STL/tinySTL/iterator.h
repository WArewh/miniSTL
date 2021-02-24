#ifndef _MYSTL_ITERATOR_H
#define _MYSTL_ITERATOR_H

#include <cstddef>

namespace mySTL
{

    struct input_iterator_tag
    {
    };  //只读
    struct output_iterator_tag
    {
    };  //只写
    struct forward_iterator_tag : public input_iterator_tag
    {
    };  //读写
    struct bidirectional_iterator_tag : public forward_iterator_tag
    {
    };  //双向移动读写
    struct random_access_iterator_tag : public bidirectional_iterator_tag
    {
    };  //随机读写

    template <class Category, class T, class Pointer = T*, class Reference = T&,
              class Distance = ptrdiff_t>
    struct iterator
    {
        using iterator_category = Category;
        using value_type = T;
        using difference_type = ptrdiff_t;
        using pointer = Pointer;
        using reference = Reference;
    };

    // traits
    template <class Iterator>
    struct iterator_traits
    {
        using iterator_category = typename Iterator::iterator_category;
        using value_type = typename Iterator::value_type;
        using difference_type = typename Iterator::difference_type;
        using pointer = typename Iterator::pointer;
        using reference = typename Iterator::reference;
    };

    //针对原生指针
    template <class T>
    struct iterator_traits<T*>
    {
        using iterator_category = random_access_iterator_tag;
        using value_type = T;
        using difference_type = ptrdiff_t;
        using pointer = T*;
        using reference = T&;
    };

    template <class T>
    struct iterator_traits<const T*>
    {
        using iterator_category = random_access_iterator_tag;
        using value_type = T;
        using difference_type = ptrdiff_t;
        using pointer = const T*;
        using const_reference = const T&;
    };

    template <class Iterator>
    inline typename iterator_traits<Iterator>::iterator_category
    iterator_category(const Iterator& It)
    {
        using category = typename iterator_traits<Iterator>::iterator_category;
        return category();
    }

    template <class Iterator>
    inline typename iterator_traits<Iterator>::value_type* value_type(const Iterator& It)
    {
        return static_cast<typename iterator_traits<Iterator>::value_type*>(0);
    }

    template <class Iterator>
    inline typename iterator_traits<Iterator>::difference_type* difference_type(const Iterator& It)
    {
        return static_cast<typename iterator_traits<Iterator>::difference_type*>(0);
    }

}  // namespace mySTL

#endif