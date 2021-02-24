#ifndef _MYSTL_SMARTPOINTER_H
#define _MYSTL_SMARTPOINTER_H

#include <cstddef>
#include <iostream>

#include "algorithm.h"

namespace mySTL
{
    //默认删除器
    template <class T>
    struct default_deleter
    {
        void operator()(T* ptr)
        {
            if (ptr)
                delete ptr;
        }
    };

    template <class T>
    struct default_deleter<T[]>
    {
        void operator()(T* ptr)
        {
            if (ptr)
                delete[] ptr;
        }
    };
}  // namespace mySTL

namespace mySTL
{

    template <class T, class D = default_deleter<T>>
    class unique_ptr
    {
    public:
        using deleter_type = D;
        using pointer = T*;
        using reference = T&;
        using const_pointer = const T*;
        using const_reference = const T&;
        explicit unique_ptr(T* ptr = nullptr) : m_data(ptr) {}
        unique_ptr(T* ptr, deleter_type del) : m_data(ptr), m_deleter(del) {}

        unique_ptr(const unique_ptr<T>&) = delete;
        unique_ptr& operator=(const unique_ptr<T>&) = delete;
        unique_ptr(unique_ptr<T>&& ptr);
        unique_ptr& operator=(unique_ptr<T>&& ptr);

        ~unique_ptr() { clean(); }

        const pointer get() const { return m_data; }
        pointer get() { return m_data; }
        reference operator*() { return *m_data; }
        pointer operator->() { return m_data; }
        const_reference operator*() const { return *m_data; }
        const_pointer operator->() const { return m_data; }

        pointer release();
        void reset(pointer ptr = nullptr);


    private:
        void clean();

    private:
        pointer m_data;
        deleter_type m_deleter;
    };
}  // namespace mySTL

namespace mySTL
{

    template <class T, class... Args>
    unique_ptr<T> make_unique(Args&&... args)
    {
        return unique_ptr<T>(new T(std::forward<Args>(args)...));
    }

    template <class T, class D>
    void swap(unique_ptr<T, D>& x, unique_ptr<T, D>& y)
    {
        mySTL::swap(x.m_data, y.m_data);
        mySTL::swap(x.m_deleter, x.m_deleter);
    }

    template <class T, class D>
    unique_ptr<T, D>::unique_ptr(unique_ptr<T>&& ptr) : m_data(nullptr)
    {
        mySTL::swap(m_data, ptr.m_data);
    }

    template <class T, class D>
    unique_ptr<T, D>& unique_ptr<T, D>::operator=(unique_ptr<T>&& ptr)
    {
        if (this != &ptr)
        {
            clean();
            mySTL::swap(*this, ptr);
        }
        return *this;
    }

    template <class T, class D>
    void unique_ptr<T, D>::clean()
    {
        m_deleter(m_data);
        m_data = nullptr;
    }

    template <class T, class D>
    typename unique_ptr<T, D>::pointer unique_ptr<T, D>::release()
    {
        T* ptr = m_data;
        m_data = nullptr;
        return ptr;
    }
    template <class T, class D>
    void unique_ptr<T, D>::reset(pointer ptr)
    {
        clean();
        m_data = ptr;
    }

}  // namespace mySTL

namespace mySTL
{
    template <class T>
    class shared_ptr;
    template <class T>
    class weak_ptr;

    struct ptrCounter
    {
        size_t shares = 0;
        size_t weaks = 0;
    };

}  // namespace mySTL

namespace mySTL
{

    template <class T>
    class shared_ptr
    {
        friend class weak_ptr<T>;

    public:
        using counter = ptrCounter;
        using pointer = T*;
        using reference = T&;
        using const_pointer = const T*;
        using const_reference = const T&;

        shared_ptr() = default;
        explicit shared_ptr(T* data);
        shared_ptr(const shared_ptr<T>& sp);
        shared_ptr(const weak_ptr<T>& wp);
        shared_ptr& operator=(const shared_ptr<T>& sp);
        ~shared_ptr() { clean(); }

        const pointer get() const { return m_data; }
        pointer get() { return m_data; }
        reference operator*() { return *m_data; }
        pointer operator->() { return m_data; }
        const_reference operator*() const { return *m_data; }
        const_pointer operator->() const { return m_data; }

        int use_count() { return (m_counter != nullptr) ? m_counter->shares : 0; }
        bool unique() { return use_count() == 1; }

        operator bool() { return m_data == nullptr ? false : true; }

    private:
        void clean();

    private:
        pointer m_data = nullptr;
        counter* m_counter = nullptr;
    };
}  // namespace mySTL

namespace mySTL
{

    template <class T, class... Args>
    shared_ptr<T> make_shared(Args&&... args)
    {
        return shared_ptr<T>(new T(std::forward<Args>(args)...));
    }

    template <class T>
    void swap(shared_ptr<T>& x, shared_ptr<T>& y)
    {
        mySTL::swap(x.m_data, y.m_data);
        mySTL::swap(x.m_counter, x.m_counter);
    }

    template <class T>
    shared_ptr<T>::shared_ptr(T* data) : m_data(data),
                                         m_counter(nullptr)
    {
        if (data != nullptr)
        {
            m_counter = new counter();
            m_counter->shares = 1;
        }
    }

    template <class T>
    shared_ptr<T>::shared_ptr(const shared_ptr<T>& sp) : m_data(sp.m_data),
                                                         m_counter(sp.m_counter)
    {
        if (m_counter != nullptr)
        {
            ++m_counter->shares;
        }
    }

    template <class T>
    shared_ptr<T>::shared_ptr(const weak_ptr<T>& wp) : m_data(wp.m_data),
                                                       m_counter(wp.m_counter)
    {
        if (m_counter != nullptr && m_counter->shares == 0)
        {
            m_data = nullptr;
        }
    }

    template <class T>
    shared_ptr<T>& shared_ptr<T>::operator=(const shared_ptr<T>& sp)
    {
        if (this == &sp)
        {
            return *this;
        }
        clean();
        m_data = sp.m_data;
        m_counter = sp.m_counter;
        if (m_counter != nullptr)
        {
            ++m_counter->shares;
        }
        return *this;
    }

    template <class T>
    void shared_ptr<T>::clean()
    {
        if (m_counter == nullptr)
            return;

        --m_counter->shares;

        if (m_counter->shares == 0)
        {
            delete m_data;
            // printf("delete m_data\n");
            if (m_counter->weaks == 0)
            {
                delete m_counter;
                // printf("delete m_counter\n");
            }
        }
    }

}  // namespace mySTL


namespace mySTL
{

    template <class T>
    class weak_ptr
    {
        friend class shared_ptr<T>;

    public:
        using counter = ptrCounter;
        using pointer = T*;
        using reference = T&;
        using const_pointer = const T*;
        using const_reference = const T&;

        weak_ptr() = default;
        weak_ptr(const weak_ptr<T>& wp);
        weak_ptr(const shared_ptr<T>& sp);
        weak_ptr& operator=(const weak_ptr<T>& wp);
        ~weak_ptr() { clean(); }

        const pointer get() const { return m_data; }
        pointer get() { return m_data; }
        reference operator*() { return *m_data; }
        pointer operator->() { return m_data; }
        const_reference operator*() const { return *m_data; }
        const_pointer operator->() const { return m_data; }

        int use_count() { return (m_counter != nullptr) ? m_counter->shares : 0; }
        bool expired();

        operator bool() { return m_data == nullptr ? false : true; }

        shared_ptr<T> lock();

    private:
        void clean();

    private:
        pointer m_data = nullptr;
        counter* m_counter = nullptr;
    };
}  // namespace mySTL

namespace mySTL
{

    template <class T>
    void swap(weak_ptr<T>& x, weak_ptr<T>& y)
    {
        mySTL::swap(x.m_data, y.m_data);
        mySTL::swap(x.m_counter, x.m_counter);
    }

    template <class T>
    weak_ptr<T>::weak_ptr(const weak_ptr<T>& wp) : m_data(wp.m_data),
                                                   m_counter(wp.m_counter)
    {
        if (m_counter != nullptr)
        {
            ++m_counter->weaks;
        }
    }

    template <class T>
    weak_ptr<T>::weak_ptr(const shared_ptr<T>& sp) : m_data(sp.m_data),
                                                     m_counter(sp.m_counter)
    {
        if (m_counter != nullptr)
        {
            ++m_counter->weaks;
        }
    }

    template <class T>
    weak_ptr<T>& weak_ptr<T>::operator=(const weak_ptr<T>& wp)
    {
        if (this == &wp)
        {
            return *this;
        }
        clean();
        m_data = wp.m_data;
        m_counter = wp.m_counter;
        if (m_counter != nullptr)
        {
            ++m_counter->weaks;
        }
        return *this;
    }
    template <class T>
    bool weak_ptr<T>::expired()
    {
        if (m_counter != nullptr && m_counter->shares > 0)
            return false;
        return true;
    }

    template <class T>
    shared_ptr<T> weak_ptr<T>::lock()
    {
        if (expired())
            return shared_ptr<T>();
        return shared_ptr<T>(*this);
    }

    template <class T>
    void weak_ptr<T>::clean()
    {
        if (m_counter == nullptr)
            return;

        --m_counter->weaks;

        if (m_counter->shares == 0 && m_counter->weaks == 0)
        {
            // std::cout << "delete m_counter\n";
            delete m_counter;
            m_counter = NULL;
        }
    }
}  // namespace mySTL


#endif