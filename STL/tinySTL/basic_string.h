#ifndef MYSTL_BASIC_STRING_H_
#define MYSTL_BASIC_STRING_H_

#include <string.h>

#include "algorithm.h"
#include "allocator.h"
#include "functional.h"

/*
    COW会导致一些问题并且在多线程情况下性能比较差劲 C++11以后使用SSO

    string的operator[]和at()会返回某个字符的引用，此时无法准确的判断程序是否修改了string的内容
    为了保COW实现的正确性，string只得统统认定operator[]和at()具有修改的“语义”

    SSO短字符串优化，因为申请堆内存的开销比较大，所以将短的字符串会被申请在栈上
*/

namespace mySTL
{

    template <typename T, typename Alloc = Allocator<T>>
    class basic_string
    {

    public:
        using value_type = T;
        using pointer = T*;
        using const_pointer = const T*;
        using size_type = size_t;
        using iterator = T*;
        using const_iterator = const T*;
        using data_allocator = Allocator<T>;

    public:
        basic_string();
        basic_string(const char* str);
        basic_string(const char* str, size_type length);
        basic_string(const basic_string& str);
        basic_string(basic_string&& str);
        void operator=(const char* str);
        void operator=(const basic_string& str);
        void operator=(basic_string&& str);
        ~basic_string();

    public:
        iterator begin() { return m_ptr; }
        iterator end() { return m_ptr + m_length; }
        bool empty() { return m_length == 0; }
        size_type size() const { return m_length; }
        size_type length() const { return m_length; }
        const_pointer c_str() const { return m_ptr; }
        const_pointer data() const { return m_ptr; }
        T& operator[](size_t i) const { return m_ptr[i]; }  //未处理越界

    public:
        basic_string& operator+=(const basic_string& str);
        basic_string& operator+=(basic_string&& str);
        basic_string& operator+=(const T* ptr);

    private:
        void alloc_aux(size_type length);
        void assign_aux(const char* ptr, size_type length);
        void append_aux(const char* ptr, size_type length);

    private:
        static const size_t kShortLength = 15 / sizeof(T);

    private:
        pointer m_ptr;
        size_type m_length;
        union
        {
            T m_buf[kShortLength + 1];
            size_type m_capacity;
        };
    };

}  // namespace mySTL

namespace mySTL
{

    template <typename T, typename Alloc>
    void basic_string<T, Alloc>::alloc_aux(size_type length)
    {
        if (m_length > kShortLength)
        {
            m_ptr = data_allocator::allocate(m_length + 1);
            m_capacity = m_length + 1;
        }
    }

    template <typename T, typename Alloc>
    basic_string<T, Alloc>::basic_string() : m_ptr(m_buf),
                                             m_length(0)
    {
        m_buf[0] = '\0';
    }

    template <typename T, typename Alloc>
    basic_string<T, Alloc>::basic_string(const char* str) : m_ptr(m_buf),
                                                            m_length(strlen(str))
    {
        alloc_aux(m_length);
        memcpy(m_ptr, str, m_length);
        m_ptr[m_length] = '\0';
    }

    template <typename T, typename Alloc>
    basic_string<T, Alloc>::basic_string(const char* str, size_type length)
        : m_ptr(m_buf),
          m_length(length)
    {
        alloc_aux(length);
        memcpy(m_ptr, str, length);
        m_ptr[length] = '\0';
    }


    template <typename T, typename Alloc>
    basic_string<T, Alloc>::basic_string(const basic_string& str)
        : m_ptr(m_buf),
          m_length(str.m_length)
    {
        alloc_aux(m_length);
        memcpy(m_ptr, str.m_ptr, m_length);
        m_ptr[m_length] = '\0';
    }

    template <typename T, typename Alloc>
    basic_string<T, Alloc>::basic_string(basic_string&& str) : m_ptr(m_buf),
                                                               m_length(str.m_length)
    {
        if (m_length <= kShortLength)
        {
            memcpy(m_ptr, str.m_ptr, m_length);
        }
        else
        {
            swap(m_length, str.m_length);
            swap(m_ptr, str.m_ptr);
            swap(m_capacity, str.m_capacity);
        }
        m_ptr[m_length] = '\0';
        str.m_ptr = nullptr;
        str.m_length = 0;
        str.m_capacity = 0;
    }

    template <typename T, typename Alloc>
    void basic_string<T, Alloc>::assign_aux(const char* ptr, size_type str_length)
    {
        if (ptr == m_ptr)
            return;
        if (str_length <= kShortLength)
        {
            if (m_length > kShortLength)
            {
                data_allocator::deallocate(m_ptr, m_capacity);
                m_ptr = m_buf;
            }
            memcpy(m_ptr, ptr, str_length);
        }
        else
        {
            if (m_length > kShortLength)
            {
                data_allocator::deallocate(m_ptr, m_capacity);
            }
            auto new_mptr = data_allocator::allocate(str_length + 1);
            memcpy(new_mptr, ptr, str_length);
            m_ptr = new_mptr;
            m_capacity = str_length + 1;
        }
        m_length = str_length;
        m_ptr[m_length] = '\0';
    }

    template <typename T, typename Alloc>
    void basic_string<T, Alloc>::operator=(const char* str)
    {
        int str_length = strlen(str);
        assign_aux(str, str_length);
    }

    template <typename T, typename Alloc>
    void basic_string<T, Alloc>::operator=(const basic_string& str)
    {
        assign_aux(str.m_ptr, str.m_length);
    }

    template <typename T, typename Alloc>
    void basic_string<T, Alloc>::operator=(basic_string&& str)
    {
        size_type str_length = str.m_length;
        if (str.m_ptr == m_ptr)
            return;
        if (str_length <= kShortLength)
        {
            if (m_length > kShortLength)
            {
                data_allocator::deallocate(m_ptr, m_capacity);
                m_ptr = m_buf;
            }
            memcpy(m_ptr, str.m_ptr, m_length);
        }
        else
        {
            m_ptr = str.m_ptr;
            m_capacity = str.m_capacity;
        }
        m_length = str_length;
        str.m_ptr = nullptr;
        str.m_length = 0;
        str.m_capacity = 0;
    }



    template <typename T, typename Alloc>
    basic_string<T, Alloc>::~basic_string()
    {
        if (m_length > kShortLength)
        {
            data_allocator::deallocate(m_ptr, m_capacity);
        }
    }

    template <typename T, typename Alloc>
    void basic_string<T, Alloc>::append_aux(const char* ptr, size_type length)
    {
        int total_length = length + m_length;

        if (total_length <= kShortLength)
        {
            memcpy(m_ptr + m_length, ptr, length);
        }
        else
        {
            if (m_length <= kShortLength)
            {
                auto ptr = data_allocator::allocate(total_length * 1.5);
                memcpy(ptr, m_ptr, m_length);
                m_capacity = total_length * 1.5;
                m_ptr = ptr;
            }
            if (m_capacity > total_length)
            {
                memcpy(m_ptr + m_length, ptr, length);
            }
            else
            {
                auto ptr = data_allocator::allocate(total_length * 1.5);
                memcpy(ptr, m_ptr, m_length);
                memcpy(ptr + m_length, ptr, length);
                data_allocator::deallocate(m_ptr, m_capacity);
                m_ptr = ptr;
                m_capacity = total_length * 1.5;
            }
        }
        m_length = total_length;
        m_ptr[m_length] = '\0';
    }

    template <typename T, typename Alloc>
    basic_string<T, Alloc>& basic_string<T, Alloc>::operator+=(const basic_string& str)
    {
        append_aux(str.m_ptr, str.m_length);
        return *this;
    }

    template <typename T, typename Alloc>
    basic_string<T, Alloc>& basic_string<T, Alloc>::operator+=(basic_string&& str)
    {
        append_aux(str.m_ptr, str.m_length);
        return *this;
    }

    template <typename T, typename Alloc>
    basic_string<T, Alloc>& basic_string<T, Alloc>::operator+=(const T* ptr)
    {
        append_aux(ptr, strlen(ptr));
        return *this;
    }

    template <typename T, typename Alloc>
    bool operator==(const basic_string<T, Alloc>& a, const basic_string<T, Alloc>& b)
    {
        size_t a_length = a.length(), b_length = b.length();
        if (a_length != b_length)
        {
            return false;
        }
        for (size_t i = 0; i < a_length; ++i)
        {
            if (a[i] != b[i])
            {
                return false;
            }
        }
        return true;
    }

    template <typename T, typename Alloc>
    bool operator!=(const basic_string<T, Alloc>& a, const basic_string<T, Alloc>& b)
    {
        return !(a == b);
    }

    template <typename T, typename Alloc>
    bool operator==(const basic_string<T, Alloc>& a, const T* data)
    {
        size_t a_length = a.length();
        size_t d_length = strlen(data);
        if (a_length != d_length)
        {
            return false;
        }
        for (size_t i = 0; i < a_length; ++i)
        {
            if (a[i] != data[i])
            {
                return false;
            }
        }
        return true;
    }

    template <typename T, typename Alloc>
    bool operator!=(const basic_string<T, Alloc>& a, const T* data)
    {
        return !(a == data);
    }

    using string = basic_string<char>;

}  // namespace mySTL
#endif