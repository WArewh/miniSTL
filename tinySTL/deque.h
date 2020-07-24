#ifndef _MYSTL_DEQUE_H
#define _MYSTL_DEQUE_H

#include "algorithm.h"
#include "allocator.h"
#include "iterator.h"


namespace mySTL {
    template <class T, size_t BufSize = 0>
    struct dequeIterator : public iterator<random_access_iterator_tag, T> {
        using value_type = T;
        using reference = T&;
        using pointer = T*;
        using size_type = size_t;
        using map_pointer = T**;
        using difference_type = ptrdiff_t;
        using iterator = dequeIterator<T, BufSize>;
        using const_iterator = dequeIterator<const T, BufSize>;

        pointer cur;
        pointer first;
        pointer last;

        map_pointer map;

        dequeIterator() : cur(nullptr), first(nullptr), last(nullptr), map(nullptr) {}

        static size_type bufferSize();
        void             setBuffer(map_pointer new_map);

        reference operator*() const { return *cur; }
        reference operator->() const { return &(operator*()); }

        difference_type operator-(const iterator& iter) const;

        iterator& operator++();
        iterator  operator++(int);
        iterator& operator--();
        iterator  operator--(int);
        iterator& operator+=(difference_type n);
        iterator  operator+(difference_type n);
        iterator& operator-=(difference_type n);
        iterator  operator-(difference_type n);

        reference operator[](difference_type n) { return *(*this + n); }

        bool operator==(const iterator& iter) { return cur == iter.cur; }
        bool operator!=(const iterator& iter) { return cur != iter.cur; }
    };
}  // namespace mySTL


// iterator
namespace mySTL {

    size_t getBufferSize(size_t n, size_t sz) { return n != 0 ? n : (sz < 512 ? 512 / sz : 1); }

    template <class T, size_t BufSize>
    inline size_t dequeIterator<T, BufSize>::bufferSize() {
        return getBufferSize(BufSize, sizeof(T));
    }

    //设置缓冲区
    template <class T, size_t BufSize>
    void dequeIterator<T, BufSize>::setBuffer(map_pointer new_map) {
        map = new_map;
        first = *new_map;
        last = first + (difference_type)bufferSize();
    }

    template <class T, size_t BufSize>
    typename dequeIterator<T, BufSize>::difference_type
    dequeIterator<T, BufSize>::operator-(const iterator& iter) const {
        if (map == iter.map)
            return cur - iter.cur;
        return difference_type(bufferSize()) * (map - iter.map - 1) + (cur - first)
               + (iter.last - iter.cur);
    }

    template <class T, size_t BufSize>
    typename dequeIterator<T, BufSize>::iterator& dequeIterator<T, BufSize>::operator++() {
        ++cur;
        if (cur == last) {
            setBuffer(map + 1);
            cur = first;
        }
        return *this;
    }
    template <class T, size_t BufSize>
    typename dequeIterator<T, BufSize>::iterator dequeIterator<T, BufSize>::operator++(int) {
        auto temp = *this;
        ++*this;
        return temp;
    }
    template <class T, size_t BufSize>
    typename dequeIterator<T, BufSize>::iterator& dequeIterator<T, BufSize>::operator--() {
        if (cur == first) {
            setBuffer(map - 1);
            cur = last;
        }
        --cur;
        return *this;
    }
    template <class T, size_t BufSize>
    typename dequeIterator<T, BufSize>::iterator dequeIterator<T, BufSize>::operator--(int) {
        auto temp = *this;
        --*this;
        return temp;
    }
    template <class T, size_t BufSize>
    typename dequeIterator<T, BufSize>::iterator&
    dequeIterator<T, BufSize>::operator+=(difference_type n) {
        difference_type offset = n + cur - first;
        difference_type bufsize = (difference_type)bufferSize();
        if (offset >= 0 && offset < bufsize) {
            cur += n;
        } else {
            difference_type map_offset =
                offset > 0 ? offset / bufsize : -((-offset - 1) / bufsize) - 1;
            cur = first + offset - map_offset * bufsize;
        }
        return *this;
    }
    template <class T, size_t BufSize>
    typename dequeIterator<T, BufSize>::iterator
    dequeIterator<T, BufSize>::operator+(difference_type n) {
        auto temp = *this;
        return temp += n;
    }
    template <class T, size_t BufSize>
    typename dequeIterator<T, BufSize>::iterator&
    dequeIterator<T, BufSize>::operator-=(difference_type n) {
        auto temp = *this;
        return temp += (-n);
    }
    template <class T, size_t BufSize>
    typename dequeIterator<T, BufSize>::iterator
    dequeIterator<T, BufSize>::operator-(difference_type n) {
        auto temp = *this;
        return temp -= n;
    }
}  // namespace mySTL


namespace mySTL {
    template <class T, class Alloc = Allocator<T>, size_t BufSize = 0>
    class deque {
    public:
        using value_type = T;
        using reference = T&;
        using pointer = T*;
        using size_type = size_t;
        using map_pointer = T**;
        using iterator = dequeIterator<T, BufSize>;
        using const_iterator = dequeIterator<const T, BufSize>;
        using data_allocator = Allocator<T>;
        using map_allocator = Allocator<T*>;

    protected:
        iterator    start;
        iterator    finish;
        map_pointer map;
        size_type   map_size;

    public:
        deque();
        explicit deque(size_type n, const T& val);
        ~deque();

    public:
        iterator       begin() { return start; }
        iterator       end() { return finish; }
        const_iterator begin() const { return start; }
        const_iterator end() const { return finish; }

        reference front() { return *start; }
        reference back() { return *(--end()); }

        size_type size() { return finish - start; }
        bool      empty() { return finish == start; }

    private:
        void createMap(size_type elems);
        void fillMap(size_type n, const T& val);

        size_type bufferSize() { return getBufferSize(BufSize, sizeof(T)); }

    public:
        void push_back(const T& val);
        void push_front(const T& val);
        void pop_back();
        void pop_front();
        void clear();
    };
}  // namespace mySTL

namespace mySTL {

    template <class T, class Alloc, size_t BufSize>
    deque<T, Alloc, BufSize>::deque() : start(),
                                        finish(),
                                        map(nullptr),
                                        map_size(0) {}
    template <class T, class Alloc, size_t BufSize>
    deque<T, Alloc, BufSize>::deque(size_type n, const T& val)
        : start(),
          finish(),
          map(nullptr),
          map_size(0) {
        createMap(n);
        fillMap(n, val);
    }

    template <class T, class Alloc, size_t BufSize>
    deque<T, Alloc, BufSize>::~deque() {
        clear();
        data_allocator::deallocate(start.first, bufferSize());
    }

    template <class T, class Alloc, size_t BufSize>
    void deque<T, Alloc, BufSize>::push_back(const T& val) {}

    template <class T, class Alloc, size_t BufSize>
    void deque<T, Alloc, BufSize>::push_front(const T& val) {}

    template <class T, class Alloc, size_t BufSize>
    void deque<T, Alloc, BufSize>::pop_back() {}

    template <class T, class Alloc, size_t BufSize>
    void deque<T, Alloc, BufSize>::pop_front() {}

    //保留一个缓冲区
    template <class T, class Alloc, size_t BufSize>
    void deque<T, Alloc, BufSize>::clear() {
        size_type bufs = bufferSize();
        for (map_pointer cur = start.map + 1; cur < finish.map; ++cur) {
            data_allocator::destroy(*cur, *cur + bufs);
            data_allocator::deallocate(*cur, bufs);
        }
        if (start.map != finish.map) {
            data_allocator::destroy(start.cur, start.last);
            data_allocator::destroy(start.first, start.cur);
            data_allocator::deallocate(finish.first, bufs);
        } else {
            data_allocator::destroy(start.cur, start.cur);
        }
    }

    template <class T, class Alloc, size_t BufSize>
    void deque<T, Alloc, BufSize>::createMap(size_type elems) {
        size_type bufs = getBufferSize(BufSize, sizeof(T));
        size_type maps = elems / bufs + 1;
        map_size = mySTL::max((size_type)8, maps + 2);  //最少八个
        map = map_allocator::allocate(map_size);

        //居中
        map_pointer temp_start = map + (map_size - maps) / 2;
        map_pointer temp_finish = temp_start + maps - 1;
        for (map_pointer cur = temp_start; cur <= temp_finish; ++cur) {
            *cur = data_allocator::allocate(bufs);
        }
        start.setBuffer(temp_start);
        finish.setBuffer(temp_finish);
        start.cur = start.first;
        finish.cur = finish.first + elems % bufs;
    }

    template <class T, class Alloc, size_t BufSize>
    void deque<T, Alloc, BufSize>::fillMap(size_type n, const T& val) {
        size_type bufs = bufferSize();
        for (map_pointer cur = start.map; cur < finish.map; ++cur) {
            mySTL::fill(*cur, *cur + bufs, val);
        }
        mySTL::fill(finish.first, finish.cur, val);
    }

}  // namespace mySTL

#endif