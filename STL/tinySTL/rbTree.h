#ifndef MYSTL_RBTREE_H
#define MYSTL_RBTREE_H

#include "allocator.h"
#include "functional.h"
#include "iterator.h"
#include "utility.h"

namespace mySTL
{

    enum class RBColor : bool
    {
        Red = true,
        Black = false
    };

    //红黑树node
    template <class T>
    struct RBNode
    {
        using value_type = T;
        using color_type = RBColor;
        using node_pointer = RBNode<T>*;

        value_type data;
        color_type color;
        node_pointer parent;
        node_pointer left;
        node_pointer right;

        RBNode(const value_type& val = value_type(), color_type col = color_type::Red,
               node_pointer p = nullptr, node_pointer l = nullptr, node_pointer r = nullptr);

        static node_pointer minimum(node_pointer ptr);
        static node_pointer maximum(node_pointer ptr);
    };
}  // namespace mySTL

namespace mySTL
{

    template <class T>
    RBNode<T>::RBNode(const value_type& val, color_type col, node_pointer p, node_pointer l,
                      node_pointer r)
        : data(val),
          color(col),
          parent(p),
          left(l),
          right(r)
    {
    }

    template <class T>
    typename RBNode<T>::node_pointer RBNode<T>::minimum(node_pointer ptr)
    {
        while (ptr->left != nullptr)
        {
            ptr = ptr->left;
        }
        return ptr;
    }

    template <class T>
    typename RBNode<T>::node_pointer RBNode<T>::maximum(node_pointer ptr)
    {
        while (ptr->right != nullptr)
        {
            ptr = ptr->right;
        }
        return ptr;
    }
}  // namespace mySTL


namespace mySTL
{
    //迭代器
    template <class T>
    struct RBTreeIterator : public iterator<bidirectional_iterator_tag, T>
    {
        using reference = T&;
        using pointer = T*;
        using iterator = RBTreeIterator<T>;
        using const_iterator = RBTreeIterator<const T>;
        using node_pointer = RBNode<T>*;

        node_pointer node;

        RBTreeIterator(node_pointer ptr = nullptr) : node(ptr) {}

        iterator& operator++();
        iterator operator++(int);
        iterator& operator--();
        iterator operator--(int);

        reference operator*() { return node->data; }
        pointer operator->() { return &(operator*()); }
    };
}  // namespace mySTL

namespace mySTL
{

    //迭代器实现 和红黑树实现有关
    template <class T>
    typename RBTreeIterator<T>::iterator& RBTreeIterator<T>::operator++()
    {
        if (node->right != nullptr)
        {
            node = node->right;
            while (node->left != nullptr)
            {
                node = node->left;
            }
        }
        else
        {
            auto temp = node->parent;
            while (node == temp->right)
            {  // 找到 不作为右子树出现的点
                node = temp;
                temp = temp->parent;
            }
            if (node->right != temp)
            {
                node = temp;
            }
        }
        return *this;
    }

    template <class T>
    typename RBTreeIterator<T>::iterator RBTreeIterator<T>::operator++(int)
    {
        auto temp = *this;
        ++*this;
        return temp;
    }

    template <class T>
    typename RBTreeIterator<T>::iterator& RBTreeIterator<T>::operator--()
    {
        if (node->color == RBColor::Red && node->parent->parent == node)
        {
            node = node->right;
        }
        else if (node->left != nullptr)
        {
            node_pointer temp = node->left;
            while (temp->right != nullptr)
            {
                temp = temp->right;
            }
            node = temp;
        }
        else
        {
            node_pointer temp = node->parent;
            while (node == temp->left)
            {  //找到 不作为左子树出现的点
                node = temp;
                temp = temp->parent;
            }
            node = temp;
        }
        return *this;
    }

    template <class T>
    typename RBTreeIterator<T>::iterator RBTreeIterator<T>::operator--(int)
    {
        auto temp = this;
        --*this;
        return temp;
    }

    template <class T>
    bool operator==(RBTreeIterator<T> it1, RBTreeIterator<T> it2)
    {
        return it1.node == it2.node;
    }

    template <class T>
    bool operator!=(RBTreeIterator<T> it1, RBTreeIterator<T> it2)
    {
        return !(it1.node == it2.node);
    }

}  // namespace mySTL

namespace mySTL
{
    template <class Key, class Value, class KeyofValue = identity<Key>, class Compare = less<Value>,
              class Alloc = Allocator<RBNode<Value>>>
    class RBTree
    {
    public:
        using value_type = Value;
        using pointer = Value*;
        using reference = Value&;
        using iterator = RBTreeIterator<Value>;
        using const_iterator = RBTreeIterator<const Value>;
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

        iterator begin() { return iterator(leftMost()); }
        iterator end() { return iterator(rightMost()); }
        size_type size() { return node_count; }
        bool empty() { return node_count == 0; }

        iterator insert(const value_type& val);
        pair<iterator, bool> insert_unique(const value_type& val);

        void clear();



    protected:
        size_type node_count = 0;
        node_pointer header;
        Compare compare;

    protected:
        node_pointer getNode() { return node_allocator::allocate(); }
        node_pointer createNode(const value_type& val);
        node_pointer cloneNode(node_pointer ptr);

        void destroyNode(node_pointer ptr);

        node_pointer& getRoot() const { return header->parent; }
        node_pointer& leftMost() const { return header->left; }
        node_pointer& rightMost() const { return header->right; }

        iterator insert_aux(node_pointer x, node_pointer y, const value_type& val);
        void clear_aux(node_pointer node);

        void leftRotate(node_pointer x, node_pointer& root);
        void rightRotate(node_pointer x, node_pointer& root);
        void reBalance(node_pointer x, node_pointer& root);

        static node_pointer minimum(node_pointer ptr) { return RBNode<Value>::minimum(ptr); }
        static node_pointer maximum(node_pointer ptr) { return RBNode<Value>::maximum(ptr); }
    };
}  // namespace mySTL

namespace mySTL
{

    template <class Key, class Value, class KeyofValue, class Compare, class Alloc>
    RBTree<Key, Value, KeyofValue, Compare, Alloc>::RBTree()
    {
        header = getNode();
        header->color = RBColor::Red;
        header->parent = nullptr;
        header->left = header;
        header->right = header;
    }

    template <class Key, class Value, class KeyofValue, class Compare, class Alloc>
    RBTree<Key, Value, KeyofValue, Compare, Alloc>::~RBTree()
    {
        clear();
        destroyNode(header);
    }

    template <class Key, class Value, class KeyofValue, class Compare, class Alloc>
    typename RBTree<Key, Value, KeyofValue, Compare, Alloc>::iterator
    RBTree<Key, Value, KeyofValue, Compare, Alloc>::insert(const value_type& val)
    {
        node_pointer node = getRoot();
        node_pointer par = header;

        while (node != 0)
        {
            par = node;
            node = compare(KeyofValue()(val), KeyofValue()(node->data)) ? node->left : node->right;
        }

        return insert_aux(node, par, val);
    }

    template <class Key, class Value, class KeyofValue, class Compare, class Alloc>
    pair<typename RBTree<Key, Value, KeyofValue, Compare, Alloc>::iterator, bool>
    RBTree<Key, Value, KeyofValue, Compare, Alloc>::insert_unique(const value_type& val)
    {
        node_pointer node = getRoot();
        node_pointer par = header;

        bool comp = true;

        while (node != 0)
        {
            par = node;
            comp = compare(KeyofValue()(val), KeyofValue()(node->data));
            node = comp ? node->left : node->right;
        }

        iterator father = iterator(par);

        if (comp)
        {
            if (father == begin())
            {
                return pair<iterator, bool>(insert_aux(node, par, val), true);
            }
            else
            {
                --father;  //
            }
        }

        if (compare(KeyofValue()(father.node->data), KeyofValue()(val)))
        {
            return pair<iterator, bool>(insert_aux(node, par, val), true);
        }

        return pair<iterator, bool>(father, false);
    }

    template <class Key, class Value, class KeyofValue, class Compare, class Alloc>
    void RBTree<Key, Value, KeyofValue, Compare, Alloc>::clear()
    {
        clear_aux(getRoot());
        node_count = 0;
        header->parent = nullptr;
        header->left = header;
        header->right = header;
    }

    template <class Key, class Value, class KeyofValue, class Compare, class Alloc>
    typename RBTree<Key, Value, KeyofValue, Compare, Alloc>::iterator
    RBTree<Key, Value, KeyofValue, Compare, Alloc>::insert_aux(node_pointer x, node_pointer y,
                                                               const value_type& val)
    {
        node_pointer node = x;
        node_pointer par = y;
        node_pointer new_node = createNode(val);
        if (par == header || node != nullptr || compare(KeyofValue()(val), KeyofValue()(par->data)))
        {
            par->left = new_node;
            if (par == header)
            {  //一个节点
                getRoot() = new_node;
                rightMost() = new_node;
            }
            else if (par == leftMost())
            {  //比最左节点还小
                leftMost() = new_node;
            }
        }
        else
        {
            par->right = new_node;
            if (par == rightMost())
            {
                rightMost() = new_node;
            }
        }
        new_node->parent = par;
        reBalance(new_node, header->parent);
        ++node_count;
        return iterator(new_node);
    }

    template <class Key, class Value, class KeyofValue, class Compare, class Alloc>
    void RBTree<Key, Value, KeyofValue, Compare, Alloc>::clear_aux(node_pointer node)
    {
        if (node == nullptr)
        {
            return;
        }
        clear_aux(node->left);
        clear_aux(node->right);
        destroyNode(node);
    }

    template <class Key, class Value, class KeyofValue, class Compare, class Alloc>
    typename RBTree<Key, Value, KeyofValue, Compare, Alloc>::node_pointer
    RBTree<Key, Value, KeyofValue, Compare, Alloc>::createNode(const value_type& val)
    {
        node_pointer temp = getNode();
        node_allocator::construct(temp, val);
        return temp;
    }

    template <class Key, class Value, class KeyofValue, class Compare, class Alloc>
    void RBTree<Key, Value, KeyofValue, Compare, Alloc>::destroyNode(node_pointer ptr)
    {
        data_allocator::destroy(&ptr->data);
        node_allocator::deallocate(ptr);
    }

    //复制颜色和数据
    template <class Key, class Value, class KeyofValue, class Compare, class Alloc>
    typename RBTree<Key, Value, KeyofValue, Compare, Alloc>::node_pointer
    RBTree<Key, Value, KeyofValue, Compare, Alloc>::cloneNode(node_pointer ptr)
    {
        node_pointer temp = createNode(ptr);
        temp->color = ptr->color;
        return temp;
    }

    template <class Key, class Value, class KeyofValue, class Compare, class Alloc>
    void RBTree<Key, Value, KeyofValue, Compare, Alloc>::leftRotate(node_pointer x,
                                                                    node_pointer& root)
    {
        node_pointer y = x->right;
        x->right = y->left;
        if (y->left != nullptr)
        {
            y->left->parent = x;
        }
        y->parent = x->parent;
        if (x == root)
        {
            root = y;
        }
        else if (x == x->parent->left)
        {
            x->parent->left = y;
        }
        else
        {
            x->parent->right = y;
        }
        y->left = x;
        x->parent = y;
    }

    template <class Key, class Value, class KeyofValue, class Compare, class Alloc>
    void RBTree<Key, Value, KeyofValue, Compare, Alloc>::rightRotate(node_pointer x,
                                                                     node_pointer& root)
    {
        node_pointer y = x->left;
        x->left = y->right;
        if (y->right != nullptr)
        {
            y->right->parent = x;
        }
        y->parent = x->parent;
        if (x == root)
        {
            root = y;
        }
        else if (x == x->parent->right)
        {
            x->parent->right = y;
        }
        else
        {
            x->parent->left = y;
        }
        y->right = x;
        x->parent = y;
    }

    template <class Key, class Value, class KeyofValue, class Compare, class Alloc>
    void RBTree<Key, Value, KeyofValue, Compare, Alloc>::reBalance(node_pointer x,
                                                                   node_pointer& root)
    {
        while (x != root && x->parent->color == RBColor::Red)
        {  //父为红

            if (x->parent == x->parent->parent->left)
            {  //父亲是爷爷的左节点

                node_pointer y = x->parent->parent->right;  //叔叔节点

                if (y && y->color == RBColor::Red)
                {  //叔叔为红

                    x->parent->color = RBColor::Black;
                    y->color = RBColor::Black;
                    x->parent->parent->color = RBColor::Red;
                    x = x->parent->parent;
                }
                else
                {  //叔叔为黑或空
                    if (x == x->parent->right)
                    {
                        x = x->parent;
                        leftRotate(x, root);
                    }
                    x->parent->color = RBColor::Black;
                    x->parent->parent->color = RBColor::Red;
                    rightRotate(x->parent->parent, root);
                }
            }
            else
            {  //父亲是爷爷的右节点

                node_pointer y = x->parent->parent->left;  //叔叔节点

                if (y && y->color == RBColor::Red)
                {

                    x->parent->color = RBColor::Black;
                    y->color = RBColor::Black;
                    x->parent->parent->color = RBColor::Red;
                    x = x->parent->parent;
                }
                else
                {

                    if (x == x->parent->left)
                    {
                        x = x->parent;
                        rightRotate(x, root);
                    }
                    x->parent->color = RBColor::Black;
                    x->parent->parent->color = RBColor::Red;
                    leftRotate(x->parent->parent, root);
                }
            }
        }
        root->color = RBColor::Black;
    }
}  // namespace mySTL

#endif