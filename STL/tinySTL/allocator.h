#ifndef _MYSTL_ALLOCATOR_H
#define _MYSTL_ALLOCATOR_H

#include <cstddef>

#include "alloc.h"
#include "construct.h"
#include "typeTraits.h"

namespace mySTL
{

    //空间配置器
    template <class T>
    class Allocator
    {
    public:
        using value_type = T;
        using pointer = T*;
        using const_pointer = const T*;
        using reference = T&;
        using const_reference = const T&;
        using size_type = size_t;
        using difference_type = ptrdiff_t;

        static T* allocate() { return static_cast<T*>(Alloc::allocate(sizeof(T))); }
        static T* allocate(size_type n);
        static void deallocate(T* ptr);
        static void deallocate(T* ptr, size_type n);

        static void construct(T* ptr) { mySTL::construct(ptr, T()); };
        static void construct(T* ptr, const T& value) { mySTL::construct(ptr, value); };
        static void destroy(T* ptr) { mySTL::destroy(ptr); };
        static void destroy(T* first, T* last);
    };
}  // namespace mySTL


namespace mySTL
{
    template <class T>
    inline T* Allocator<T>::allocate(size_type n)
    {
        return n == 0 ? 0 : static_cast<T*>(Alloc::allocate(n * sizeof(T)));
    }

    template <class T>
    inline void Allocator<T>::deallocate(T* ptr)
    {
        Alloc::deallocate(static_cast<void*>(ptr), sizeof(T));
    }

    template <class T>
    inline void Allocator<T>::deallocate(T* ptr, size_type n)
    {
        if (n != 0)
            Alloc::deallocate(static_cast<void*>(ptr), n * sizeof(T));
    }

    template <class T>
    inline void Allocator<T>::destroy(T* first, T* last)
    {
        using trivial_destructor = typename _type_traits<T>::has_trivial_destructor;
        mySTL::_destroy(first, last, trivial_destructor());
    }

};  // namespace mySTL


#endif