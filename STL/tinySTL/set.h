#ifndef _MYSTL_SET_H
#define _MYSTL_SET_H

#include "rbTree.h"

namespace mySTL
{
    template <class Key, class Value = Key, class Compare = less<Key>,
              class Alloc = Allocator<RBNode<Key>>>
    class set
    {
    public:
        using key_type = Key;
        using value_type = Key;
        using key_compare = Compare;
        using value_compare = Compare;

    private:
        using tree_type = RBTree<key_type, value_type, identity<Key>, Compare, Alloc>;

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
        set() : t() {}
        ~set() {}

        iterator begin() { return t.begin(); }
        iterator end() { return t.end(); }

        size_type size() { return t.size(); }
        bool empty() { return t.empty(); }

        pair<iterator, bool> insert(const value_type& val) { return t.insert_unique(val); }

        void clear() { return t.clear(); }
    };

}  // namespace mySTL

namespace mySTL
{
    // template <class Key,class Value, class Compare, class Alloc>
}

#endif
