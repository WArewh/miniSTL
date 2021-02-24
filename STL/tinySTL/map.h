#ifndef _MYSTL_MAP_H
#define _MYSTL_MAP_H

#include "rbTree.h"
#include "utility.h"

namespace mySTL
{
    template <class Key, class Value, class Compare = less<Key>,
              class Alloc = Allocator<RBNode<Key>>>
    class map
    {
    public:
        using key_type = Key;
        using data_type = Value;
        using mapped_type = Value;
        using value_type = pair<Key, Value>;

    private:
        using tree_type = RBTree<key_type, value_type, select1st<value_type>, Compare, Alloc>;

    public:
        using pointer = typename tree_type::pointer;
        using const_pointer = typename tree_type::const_pointer;
        using reference = typename tree_type::reference;
        using const_reference = typename tree_type::const_reference;
        using iterator = typename tree_type::iterator;
        using const_iterator = typename tree_type::const_iterator;
        using size_type = typename tree_type::size_type;
        using difference_type = typename tree_type::difference_type;

    private:
        tree_type t;

    public:
        map() : t() {}

        iterator begin() { return t.begin(); }
        iterator end() { return t.end(); }

        size_type size() { return t.size(); }
        bool empty() { return t.empty(); }

        pair<iterator, bool> insert(const value_type& val) { return t.insert_unique(val); }

        void clear() { return t.clear(); }

        data_type& operator[](const key_type& key)
        {
            return ((*(insert(value_type(key, data_type())).first)).second);
        }
    };
}  // namespace mySTL

#endif