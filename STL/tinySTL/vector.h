#ifndef _MYSTL_VECTOR_H
#define _MYSTL_VECTOR_H

#include "algorithm.h"
#include "allocator.h"
#include "uninitial.h"

namespace mySTL
{
    template <class T, class Alloc = Allocator<T>>
    class vector
    {
    public:
        using value_type = T;
        using pointer = T*;
        using iterator = T*;
        using reference = T&;
        using size_type = size_t;
        using difference_type = ptrdiff_t;

    private:
        using data_allocator = Alloc;
        iterator start;           //使用的头部
        iterator finish;          //使用的尾部
        iterator end_of_storage;  //总共可用的尾部

    public:
        //构造，复制，析构
        vector();
        vector(const size_type n, const value_type& value);
        vector(const vector& v);
        vector(vector&& v);
        ~vector();
        explicit vector(const size_type n);
        vector& operator=(const vector& v);
        vector& operator=(vector&& v);

        //迭代器相关
        iterator begin() { return start; }
        iterator end() { return finish; }
        reference front() { return *start; }
        reference back() { return *(finish - 1); }

        //与容量相关
        size_type size() const { return finish - start; }
        size_type capacity() const { return end_of_storage - start; }

        bool empty() const { return start == finish; }
        void resize(size_type n, value_type val = value_type());
        void reserve(size_type n);
        void shrink_to_fit();

        //访问元素相关
        reference operator[](const difference_type& i) { return *(start + i); }
        iterator operator+(const size_type& n) { return start + n; }

        //容器修改
        void clear();
        void swap(vector& v);
        void push_back(const value_type& value);
        void pop_back();

        void insert(iterator pos, const value_type& val);
        void insert(iterator pos, const size_type& n, const value_type& val);

        iterator erase(iterator pos);
        iterator erase(iterator first, iterator last);

        //逻辑比较
        bool operator==(const vector& v) const;
        bool operator!=(const vector& v) const;

    private:
        //辅助函数
        void allocateAndFillN(const size_type n, const value_type& value);
        template <class InputIterator>
        void allocateAndCopy(InputIterator first, InputIterator last);
        void destroyAndDeallocateAll();
        size_t getNewCapacity(size_t new_size);
    };

}  // namespace mySTL



// vector方法实现
namespace mySTL
{

    //辅助函数
    template <class T, class Alloc>
    void vector<T, Alloc>::allocateAndFillN(const size_type size, const value_type& value)
    {
        start = data_allocator::allocate(size);
        finish = mySTL::uninitialized_fill_n(start, size, value);
        end_of_storage = finish;
    }
    template <class T, class Alloc>
    template <class InputIterator>
    void vector<T, Alloc>::allocateAndCopy(InputIterator first, InputIterator last)
    {
        start = data_allocator::allocate(last - first);
        finish = mySTL::uninitialized_copy(first, last, start);
        end_of_storage = finish;
    }

    template <class T, class Alloc>
    void vector<T, Alloc>::destroyAndDeallocateAll()
    {
        if (capacity() != 0)
        {
            data_allocator::destroy(start, finish);
            data_allocator::deallocate(start, capacity());
        }
    }

    template <class T, class Alloc>
    size_t vector<T, Alloc>::getNewCapacity(size_t size)
    {
        return mySTL::max((size_t)2 * capacity(), size);
    }


    //构造，复制，析构
    template <class T, class Alloc>
    vector<T, Alloc>::vector() : start(nullptr),
                                 finish(nullptr),
                                 end_of_storage(nullptr)
    {
    }

    template <class T, class Alloc>
    vector<T, Alloc>::vector(const size_type n, const value_type& value)
    {
        allocateAndFillN(n, value);
    }

    template <class T, class Alloc>
    vector<T, Alloc>::vector(const vector& v)
    {
        allocateAndCopy(v.start, v.finish);
    }

    template <class T, class Alloc>
    vector<T, Alloc>::vector(vector&& v)
    {
        start = v.start;
        finish = v.finish;
        end_of_storage = v.end_of_storage;
        v.start = v.finish = v.end_of_storage = 0;
    }

    template <class T, class Alloc>
    vector<T, Alloc>::vector(const size_type n)
    {
        allocateAndFillN(n, value_type());
    }

    template <class T, class Alloc>
    vector<T, Alloc>& vector<T, Alloc>::operator=(const vector& v)
    {
        if (this != &v)
        {
            allocateAndCopy(v.start, v.finish);
        }
        return *this;
    }

    template <class T, class Alloc>
    vector<T, Alloc>& vector<T, Alloc>::operator=(vector&& v)
    {
        if (this != &v)
        {
            destroyAndDeallocateAll();
            start = v.start;
            finish = v.finish;
            end_of_storage = v.end_of_storage;
            v.start = v.finish = v.end_of_storage = 0;
        }
        return *this;
    }

    template <class T, class Alloc>
    vector<T, Alloc>::~vector()
    {
        destroyAndDeallocateAll();
    }

    //与容量相关
    template <class T, class Alloc>
    void vector<T, Alloc>::resize(size_type n, value_type val)
    {
        if (n < size())
        {
            data_allocator::destroy(start + n, finish);
            finish = start + n;
        }
        else if (n > size() && n <= capacity())
        {
            size_t inserts = n - size();  //插入个数

            finish = mySTL::uninitialized_fill_n(finish, inserts, val);
        }
        else
        {
            size_t new_size = getNewCapacity(n);
            size_t inserts = n - size();  //插入个数

            T* new_start = data_allocator::allocate(getNewCapacity(new_size));
            T* new_finish = mySTL::uninitialized_copy(begin(), end(), new_start);
            new_finish = mySTL::uninitialized_fill_n(new_finish, inserts, val);

            destroyAndDeallocateAll();

            start = new_start;
            finish = new_finish;
            end_of_storage = start + new_size;
        }
    }

    template <class T, class Alloc>
    void vector<T, Alloc>::reserve(size_type n)
    {
        if (n <= capacity())
        {
            return;
        }
        T* new_start = data_allocator::allocate(n);

        T* new_finish = mySTL::uninitialized_copy(start, finish, new_start);

        destroyAndDeallocateAll();

        start = new_start;
        finish = new_finish;
        end_of_storage = start + n;
    }
    template <class T, class Alloc>
    void vector<T, Alloc>::shrink_to_fit()
    {
        //会有问题
        // data_allocator::deallocate(finish, end_of_storage - finish);
        // end_of_storage = finish;
        T* new_start = data_allocator::allocate(size());
        finish = mySTL::uninitialized_copy(start, finish, new_start);
        destroyAndDeallocateAll();
        start = new_start;
        end_of_storage = finish;
    }

    //容器修改
    template <class T, class Alloc>
    void vector<T, Alloc>::clear()
    {
        data_allocator::destroy(start, finish);
        finish = start;
    }

    template <class T, class Alloc>
    void vector<T, Alloc>::swap(vector& v)
    {
        mySTL::swap(start, v.start);
        mySTL::swap(finish, v.finish);
        mySTL::swap(end_of_storage, v.end_of_storage);
    }

    template <class T, class Alloc>
    void vector<T, Alloc>::push_back(const value_type& value)
    {
        insert(finish, 1, value);
    }
    template <class T, class Alloc>
    void vector<T, Alloc>::pop_back()
    {
        data_allocator::destroy(--finish);
    }

    template <class T, class Alloc>
    void vector<T, Alloc>::insert(iterator pos, const value_type& val)
    {
        insert(pos, 1, val);
    }

    template <class T, class Alloc>
    void vector<T, Alloc>::insert(iterator pos, const size_type& n, const value_type& val)
    {
        size_t total_size = size() + n;
        if (total_size <= capacity())
        {
            size_t after_pos_size = finish - pos;
            iterator old_finish = finish;
            if (after_pos_size > n)
            {
                size_t diff = after_pos_size - n;
                mySTL::copy(finish - n, finish, finish);
                finish += n;
                mySTL::copy(pos, pos + diff, finish);
                mySTL::fill_n(pos, n, val);
            }
            else
            {
                size_t diff = n - after_pos_size;
                mySTL::fill_n(finish, diff, val);
                finish += diff;
                mySTL::copy(pos, old_finish, finish);
                mySTL::fill(pos, old_finish, val);
            }
        }
        else
        {
            total_size = getNewCapacity(total_size);
            iterator new_start = data_allocator::allocate(total_size);
            iterator new_finish = new_start;
            new_finish = mySTL::copy(start, pos, new_start);
            new_finish = mySTL::fill_n(new_finish, n, val);
            new_finish = mySTL::copy(pos, finish, new_finish);
            destroyAndDeallocateAll();
            start = new_start;
            finish = new_finish;
            end_of_storage = new_start + total_size;
        }
    }

    template <class T, class Alloc>
    typename vector<T, Alloc>::iterator vector<T, Alloc>::erase(iterator pos)
    {
        return erase(pos, pos + 1);
    }

    template <class T, class Alloc>
    typename vector<T, Alloc>::iterator vector<T, Alloc>::erase(iterator first, iterator last)
    {
        auto iter = mySTL::copy(last, finish, first);
        data_allocator::destroy(iter, finish);
        finish = finish - (last - first);
        return first;
    }

    //逻辑比较

    template <class T, class Alloc>
    bool vector<T, Alloc>::operator==(const vector& v) const
    {
        if (size() != v.size())
        {
            return false;
        }
        else
        {
            auto ptr1 = start;
            auto ptr2 = v.start;
            for (; ptr1 != finish && ptr2 != v.finish; ++ptr1, ++ptr2)
            {
                if (*ptr1 != *ptr2)
                    return false;
            }
            return true;
        }
    }
    template <class T, class Alloc>
    bool vector<T, Alloc>::operator!=(const vector& v) const
    {
        return !((*this).operator==(v));
    }

    template <class T, class Alloc>
    bool operator==(const vector<T, Alloc>& v1, const vector<T, Alloc>& v2)
    {
        return v1.operator==(v2);
    }
    template <class T, class Alloc>
    bool operator!=(const vector<T, Alloc>& v1, const vector<T, Alloc>& v2)
    {
        return v1.operator!=(v2);
    }

}  // namespace mySTL

#endif