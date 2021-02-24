#ifndef _MYSTL_LIST_H
#define _MYSTL_LIST_H

#include "algorithm.h"
#include "allocator.h"
#include "iterator.h"

namespace mySTL
{

    template <class T>
    struct ListNode
    {
        using pointer = ListNode<T>*;
        T data;
        pointer prev;
        pointer next;
        ListNode(const T& d, pointer p = nullptr, pointer n = nullptr) : data(d), prev(p), next(n)
        {
        }
    };

    template <class T>
    struct listIterator : public iterator<bidirectional_iterator_tag, T>
    {
        using node_ptr = ListNode<T>*;
        using reference = T&;
        using pointer = T*;

        node_ptr ptr;
        explicit listIterator(node_ptr p = nullptr) : ptr(p) {}

        listIterator& operator++();
        listIterator operator++(int);
        listIterator& operator--();
        listIterator operator--(int);

        reference operator*() { return ptr->data; }
        pointer operator->() { return &(operator*()); }

        bool operator==(const listIterator<T>& rhs) { return ptr->data == rhs.ptr->data; }
        bool operator!=(const listIterator<T>& rhs) { return ptr->data != rhs.ptr->data; }
    };
}  // namespace mySTL


namespace mySTL
{

    // iterator

    template <class T>
    listIterator<T>& listIterator<T>::operator++()
    {
        ptr = ptr->next;
        return *this;
    }
    template <class T>
    listIterator<T> listIterator<T>::operator++(int)
    {
        auto temp = *this;
        ++*this;
        return temp;
    }
    template <class T>
    listIterator<T>& listIterator<T>::operator--()
    {
        ptr = ptr->prev;
        return *this;
    }
    template <class T>
    listIterator<T> listIterator<T>::operator--(int)
    {
        auto temp = *this;
        --*this;
        return temp;
    }
}  // namespace mySTL


namespace mySTL
{

    //双向环形链表 有问题
    template <class T, class Alloc = Allocator<ListNode<T>>>
    class list
    {
    public:
        using value_type = T;
        using reference = T&;
        using size_type = size_t;
        using iterator = listIterator<T>;
        using const_iterator = const listIterator<T>;
        using node_ptr = ListNode<T>*;
        using node_allocator = Alloc;

    protected:
        node_ptr node;

    public:
        list();
        explicit list(size_type n, const value_type& val = value_type());
        list(const list& li);
        list& operator=(const list& li);
        ~list();

    public:
        iterator begin() { return listIterator<T>(node->next); }
        iterator end() { return listIterator<T>(node); }
        const_iterator begin() const { return listIterator<T>(node->next); }
        const_iterator end() const { return listIterator<T>(node); }

        size_type size() { return distance(begin(), end()); }
        bool empty() const { return node == node->next; }

        reference front() { return *begin(); }
        reference back() { return *(--end()); }

        void push_front(const value_type& val) { insert(begin(), val); }
        void pop_front() { erase(begin()); }
        void push_back(const value_type& val) { insert(end(), val); }
        void pop_back() { erase(--end()); }

        iterator insert(iterator pos, const value_type& val);

        void remove(const value_type& val);
        void clear();
        void reverse();

        iterator erase(iterator pos);

        void splice(iterator pos, list& li);

    protected:
        node_ptr getNode() { return node_allocator::allocate(); }
        void freeNode(node_ptr ptr) { return node_allocator::deallocate(ptr); }
        node_ptr createNode(const T& val = T());
        void destoryNode(node_ptr ptr);
        void transfer(iterator pos, iterator first, iterator last);
    };
}  // namespace mySTL


namespace mySTL
{

    // list

    template <class T, class Alloc>
    list<T, Alloc>::list() : node(createNode())
    {
        node->next = node->prev = node;
    }

    template <class T, class Alloc>
    list<T, Alloc>::list(size_type n, const value_type& val) : node(getNode())
    {
        node->next = node->prev = node;
        for (size_type i = 0; i < n; ++i)
        {
            push_back(val);
        }
    }

    template <class T, class Alloc>
    list<T, Alloc>::list(const list<T, Alloc>& li) : node(getNode())
    {
        node->next = node->prev = node;
        for (auto iter = li.begin(); iter != li.end(); ++iter)
        {
            push_back(*iter);
        }
    }
    template <class T, class Alloc>
    list<T, Alloc>& list<T, Alloc>::operator=(const list& li)
    {
        if (li != *this)
        {
            clear();
            node->next = node->prev = node;
            for (auto iter = li.begin(); iter != end(); ++iter)
            {
                push_back(*iter);
            }
        }
    }
    template <class T, class Alloc>
    list<T, Alloc>::~list()
    {
        clear();
        destoryNode(node);
    }

    template <class T, class Alloc>
    typename list<T, Alloc>::node_ptr list<T, Alloc>::createNode(const T& val)
    {
        node_ptr ptr = getNode();
        node_allocator::construct(ptr, val);
        return ptr;
    }
    template <class T, class Alloc>
    void list<T, Alloc>::destoryNode(node_ptr ptr)
    {
        mySTL::destroy(&(ptr->data));
        freeNode(ptr);
    }

    //插在pos前
    template <class T, class Alloc>
    typename list<T, Alloc>::iterator list<T, Alloc>::insert(iterator pos, const value_type& val)
    {
        node_ptr temp = createNode(val);
        temp->next = pos.ptr;
        temp->prev = pos.ptr->prev;
        pos.ptr->prev->next = temp;
        pos.ptr->prev = temp;
        return listIterator<T>(temp);
    }

    template <class T, class Alloc>
    void list<T, Alloc>::remove(const value_type& val)
    {
        iterator first = begin(), last = end();
        while (first != last)
        {
            iterator temp = first;
            ++temp;
            if (first.ptr->data == val)
                erase(first);
            first = temp;
        }
    }

    template <class T, class Alloc>
    void list<T, Alloc>::clear()
    {
        node_ptr cur = begin().ptr;
        while (cur != node)
        {
            node_ptr temp = cur;
            cur = cur->next;
            destoryNode(temp);
        }
        node->prev = node;
        node->next = node;
    }

    template <class T, class Alloc>
    void list<T, Alloc>::reverse()
    {
        if (node->next == node || node->next->next == node)
        {
            return;
        }
        iterator first = begin();
        ++first;
        while (first != end())
        {
            iterator temp = first;
            ++first;
            transfer(begin(), temp, first);
        }
    }

    //返回删除的下一个位置
    template <class T, class Alloc>
    typename list<T, Alloc>::iterator list<T, Alloc>::erase(iterator pos)
    {
        node_ptr prev_node = pos.ptr->prev;
        node_ptr next_node = pos.ptr->next;
        prev_node->next = next_node;
        next_node->prev = prev_node;
        destoryNode(pos.ptr);
        return iterator(next_node);
    }

    //将[first,last)移动到pos之前
    template <class T, class Alloc>
    void list<T, Alloc>::transfer(iterator pos, iterator first, iterator last)
    {
        if (pos != last)
        {
            last.ptr->prev->next = pos.ptr;
            first.ptr->prev->next = last.ptr;
            pos.ptr->prev->next = first.ptr;
            auto temp = pos.ptr->prev;
            pos.ptr->prev = last.ptr->prev;
            last.ptr->prev = first.ptr->prev;
            first.ptr->prev = temp;
        }
    }

    template <class T, class Alloc>
    void list<T, Alloc>::splice(iterator pos, list<T, Alloc>& li)
    {
        if (!li.empty())
        {
            transfer(pos, li.begin(), li.end());
        }
    }

    //逻辑
    template <class T, class Alloc>
    bool operator==(list<T, Alloc>& lhs, list<T, Alloc>& rhs)
    {
        auto left_iter = lhs.begin(), right_iter = rhs.begin();
        auto left_end = lhs.end(), right_end = rhs.end();

        while (*left_iter == *right_iter)
        {
            if (left_iter == left_end || right_iter == right_end)
                break;
            ++left_iter;
            ++right_iter;
        }

        if (left_iter == left_end && right_iter == right_end)
        {
            return true;
        }
        return false;
    }

    template <class T, class Alloc>
    bool operator!=(list<T, Alloc>& lhs, list<T, Alloc>& rhs)
    {
        return !(lhs == rhs);
    }


    //交换
    template <class T, class Alloc>
    void swap(list<T, Alloc>& x, list<T, Alloc>& y)
    {
        swap(x.node, y.node);
    }


}  // namespace mySTL

#endif