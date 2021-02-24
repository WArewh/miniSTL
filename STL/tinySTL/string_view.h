#ifndef MYSTL_STRING_VIEW_H_
#define MYSTL_STRING_VIEW_H_

#include <string.h>

#include "basic_string.h"

namespace mySTL
{

    class string_view
    {
    public:
        using value_type = char;
        using pointer = char*;
        using const_pointer = const char*;
        using size_type = size_t;
        using iterator = char*;
        using const_iterator = const char*;

    public:
        string_view() : m_ptr(NULL), m_length(0) {}
        string_view(const char* str) : m_ptr(str), m_length(static_cast<int>(strlen(m_ptr))) {}

        string_view(const unsigned char* str)
            : m_ptr(reinterpret_cast<const char*>(str)),
              m_length(static_cast<int>(strlen(m_ptr)))
        {
        }

        string_view(const string& str) : m_ptr(str.data()), m_length(static_cast<int>(str.size()))
        {
        }

        string_view(const char* ptr, int len) : m_ptr(ptr), m_length(len) {}

        const_pointer data() const { return m_ptr; }
        size_type size() const { return m_length; }
        size_type length() const { return m_length; }
        bool empty() const { return m_length == 0; }
        const_pointer begin() const { return m_ptr; }
        const_pointer end() const { return m_ptr + m_length; }
        char operator[](int i) const { return m_ptr[i]; }

        void clear()
        {
            m_ptr = NULL;
            m_length = 0;
        }
        void set(const char* buffer, int len)
        {
            m_ptr = buffer;
            m_length = len;
        }
        void set(const char* str)
        {
            m_ptr = str;
            m_length = static_cast<int>(strlen(str));
        }

        void set(const void* buffer, int len)
        {
            m_ptr = reinterpret_cast<const char*>(buffer);
            m_length = len;
        }

        void remove_prefix(int n)
        {
            m_ptr += n;
            m_length -= n;
        }
        void remove_suffix(int n) { m_length -= n; }

        mySTL::string as_string() const { return mySTL::string(data(), size()); }


    private:
        const char* m_ptr;
        int m_length;
    };
}  // namespace mySTL

namespace mySTL
{
    bool operator==(const string_view& v1, const string_view& v2)
    {
        return ((v1.length() == v2.length()) && (memcmp(v1.data(), v2.data(), v1.length()) == 0));
    }
    bool operator!=(const string_view& v1, const string_view& v2) { return !(v1 == v2); }
}  // namespace mySTL


#endif