#ifndef _MYSTL_CONSTRUCT_H
#define _MYSTL_CONSTRUCT_H

#include <cstdlib>

#include "typeTraits.h"

namespace mySTL {

    template <class T1, class T2>
    inline void construct(T1* ptr1, const T2& value) {
        new (ptr1) T1(value);
    }

    template <class T>
    inline void destroy(T* ptr) {
        ptr->~T();
    }

    template <class ForwardIterator>
    inline void _destroy(ForwardIterator first, ForwardIterator last, _true_type) {}

    template <class ForwardIterator>
    void _destroy(ForwardIterator first, ForwardIterator last, _false_type) {
        for (; first != last; ++first) {
            destroy(&*first);
        }
    }

}  // namespace mySTL

#endif