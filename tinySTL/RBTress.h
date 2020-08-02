#ifndef MYSTL_RBTREE_H
#define MYSTL_RBTREE_H

#include "allocator.h"
#include "functional.h"
#include "iterator.h"

namespace mySTL {

    enum class RBColor : bool
    {
        Red = 0,
        Black = 1
    };

    //红黑树node
    template <class T>
    struct RBNode {
        using value_type = T;
        using color_type = RBColor;
        using node_pointer = RBNode<T>*;

        value_type   data;
        color_type   color;
        node_pointer parent;
        node_pointer left;
        node_pointer right;

        RBNode(const value_type& val = value_type(), color_type col = color_type::Red,
               node_pointer p = nullptr, node_pointer l = nullptr, node_pointer r = nullptr);

        static node_pointer minimum(node_pointer ptr);
        static node_pointer maximum(node_pointer ptr);
    };
}  // namespace mySTL

namespace mySTL {

    template <class T>
    RBNode<T>::RBNode(const value_type& val, color_type col, node_pointer p, node_pointer l,
                      node_pointer r)
        : data(val),
          color(col),
          parent(p),
          left(l),
          right(r) {}

    template <class T>
    typename RBNode<T>::node_pointer RBNode<T>::minimum(node_pointer ptr) {
        while (ptr->left != nullptr) {
            ptr = ptr->left;
        }
        return ptr;
    }

    template <class T>
    typename RBNode<T>::node_pointer RBNode<T>::maximum(node_pointer ptr) {
        while (ptr->right != nullptr) {
            ptr = ptr->right;
        }
        return ptr;
    }
}  // namespace mySTL


namespace mySTL {
    //迭代器
    template <class T>
    struct RBTreeIterator : public iterator<bidirectional_iterator_tag, T> {
        using reference = T&;
        using pointer = T*;
        using iterator = RBTreeIterator<T>;
        using const_iterator = RBTreeIterator<const T>;
        using node_pointer = RBNode<T>*;

        node_pointer node;

        RBTreeIterator(node_pointer ptr = nullptr) : node(ptr) {}

        iterator& operator++();
        iterator  operator++(int);
        iterator& operator--();
        iterator  operator--(int);

        reference operator*() { return node->data; }
        pointer   operator->() { return &(operator*()); }
    };
}  // namespace mySTL

namespace mySTL {

    //迭代器实现 和红黑树实现有关
    template <class T>
    typename RBTreeIterator<T>::iterator& RBTreeIterator<T>::operator++() {
        if (node->right != nullptr) {
            node = node->right;
            while (node->left != nullptr) {
                node = node->left;
            }
        } else {
            auto temp = node->parent;
            while (node == temp->right) {  // 找到 不作为右子树出现的点
                node = temp;
                temp = temp->parent;
            }
            if (node->right != temp) {
                node = temp;
            }
        }
        return *this;
    }

    template <class T>
    typename RBTreeIterator<T>::iterator RBTreeIterator<T>::operator++(int) {
        auto temp = *this;
        ++*this;
        return temp;
    }

    template <class T>
    typename RBTreeIterator<T>::iterator& RBTreeIterator<T>::operator--() {
        if (node->color == RBColor::Red && node->parent->parent == node) {
            node = node->right;
        } else if (node->left != nullptr) {
            node_pointer temp = node->left;
            while (temp->right != nullptr) {
                temp = temp->right;
            }
            node = temp;
        } else {
            node_pointer temp = node->parent;
            while (node == temp->left) {  //找到 不作为左子树出现的点
                node = temp;
                temp = temp->parent;
            }
            node = temp;
        }
        return *this;
    }

    template <class T>
    typename RBTreeIterator<T>::iterator RBTreeIterator<T>::operator--(int) {
        auto temp = this;
        --*this;
        return temp;
    }
}  // namespace mySTL

namespace mySTL {
    template <class Key, class Value, class Compare = less<Value>,
              class Alloc = Allocator<RBNode<Value>>>
    class RBTree {
    public:
        using key_type = Key;
        using value_type = Value;
        using pointer = Value*;
        using reference = Value&;
        using iterator = RBTreeIterator<Value>;
        using const_pointer = const Value*;
        using const_reference = const Value&;
        using size_type = size_t;
        using difference_type = ptrdiff_t;

    protected:
        using node_allocator = Allocator<RBNode<Value>>;
        using data_allocator = Allocator<Value>;
        using node_pointer = RBNode<Value>*;
        using color_type = typename RBNode<Value>::color_type;

    public:
        RBTree();
        ~RBTree();
        size_type size() { return node_count; }
        bool      empty() { return node_count == 0; }

        iterator insert(const value_type& val);



    protected:
        size_type    node_count;
        node_pointer header;
        Compare      key_compare;

    protected:
        node_pointer getNode() { return node_allocator::allocator(); }
        node_pointer destroyNode(node_pointer ptr);
        node_pointer createNode(const value_type& val);
        node_pointer cloneNode(node_pointer ptr);

        node_pointer& root() const { return header->parent; }
        node_pointer& leftMost() const { return header->left; }
        node_pointer& rightMost() const { return header->right; }

        iterator insert_aux(node_pointer, node_pointer, const value_type& val);

        void leftRotate(node_pointer*, node_pointer*&);
        void rightRotate(node_pointer*, node_pointer*&);
    };
}  // namespace mySTL

namespace mySTL {

    template <class Key, class Value, class Compare, class Alloc>
    RBTree<Key, Value, Compare, Alloc>::RBTree() {
        header = getNode();
        header->color = RBColor::Red;
        header->parent = nullptr;
        header->left = header;
        header->right = header;
    }

    template <class Key, class Value, class Compare, class Alloc>
    RBTree<Key, Value, Compare, Alloc>::~RBTree() {
        // clear();
        destroyNode(header);
    }

    template <class Key, class Value, class Compare, class Alloc>
    typename RBTree<Key, Value, Compare, Alloc>::iterator
    RBTree<Key, Value, Compare, Alloc>::insert(const value_type& val) {}

    // template <class Key, class Value, class Compare, class Alloc>
    // void RBTree<Key, Value, Compare, Alloc>::erase() {}

    // template <class Key, class Value, class Compare, class Alloc>
    // void RBTree<Key, Value, Compare, Alloc>::clear() {}

    template <class Key, class Value, class Compare, class Alloc>
    typename RBTree<Key, Value, Compare, Alloc>::iterator
    RBTree<Key, Value, Compare, Alloc>::insert_aux(node_pointer, node_pointer,
                                                   const value_type& val) {}

    template <class Key, class Value, class Compare, class Alloc>
    typename RBTree<Key, Value, Compare, Alloc>::node_pointer
    RBTree<Key, Value, Compare, Alloc>::createNode(const value_type& val) {
        auto temp = getNode();
        node_allocator::construct(temp, val);
        return temp;
    }

    template <class Key, class Value, class Compare, class Alloc>
    typename RBTree<Key, Value, Compare, Alloc>::node_pointer
    RBTree<Key, Value, Compare, Alloc>::destroyNode(node_pointer ptr) {
        destroy(ptr->data);
        node_allocator::deallocate(ptr);
    }

    //复制颜色和数据
    template <class Key, class Value, class Compare, class Alloc>
    typename RBTree<Key, Value, Compare, Alloc>::node_pointer
    RBTree<Key, Value, Compare, Alloc>::cloneNode(node_pointer ptr) {
        node_pointer temp = createNode(ptr);
        temp->color = ptr->color;
        return temp;
    }
}  // namespace mySTL

#endif