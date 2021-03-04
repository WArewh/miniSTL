#ifndef _MYSTL_DEQUE_H
#define _MYSTL_DEQUE_H

#include "algorithm.h"
#include "allocator.h"
#include "iterator.h"


namespace mySTL
{
    template <class T, size_t BufSize = 0>
    struct dequeIterator : public iterator<random_access_iterator_tag, T>
    {
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

        dequeIterator(pointer ptr = nullptr) : cur(ptr), first(ptr), last(ptr), map(nullptr) {}

        static size_type bufferSize();
        void setBuffer(map_pointer new_map);

        reference operator*() const { return *cur; }
        reference operator->() const { return &(operator*()); }

        difference_type operator-(const iterator& iter) const;

        iterator& operator++();
        iterator operator++(int);
        iterator& operator--();
        iterator operator--(int);
        iterator& operator+=(difference_type n);
        iterator operator+(difference_type n);
        iterator& operator-=(difference_type n);
        iterator operator-(difference_type n);

        reference operator[](difference_type n) { return *(*this + n); }

        bool operator==(const iterator& iter) { return cur == iter.cur; }
        bool operator!=(const iterator& iter) { return cur != iter.cur; }
    };
}  // namespace mySTL


// iterator
namespace mySTL
{

    static inline size_t getDequeBufferSize(size_t n, size_t sz)
    {
        return n != 0 ? n : (sz < 512 ? 512 / sz : 1);
    }

    template <class T, size_t BufSize>
    inline size_t dequeIterator<T, BufSize>::bufferSize()
    {
        return getDequeBufferSize(BufSize, sizeof(T));
    }

    //设置缓冲区
    template <class T, size_t BufSize>
    void dequeIterator<T, BufSize>::setBuffer(map_pointer new_map)
    {
        map = new_map;
        first = *new_map;
        last = first + (difference_type)bufferSize();
    }

    template <class T, size_t BufSize>
    typename dequeIterator<T, BufSize>::difference_type
    dequeIterator<T, BufSize>::operator-(const iterator& iter) const
    {
        return difference_type(bufferSize()) * (map - iter.map - 1) + (cur - first)
               + (iter.last - iter.cur);
    }

    template <class T, size_t BufSize>
    typename dequeIterator<T, BufSize>::iterator& dequeIterator<T, BufSize>::operator++()
    {
        ++cur;
        if (cur == last)
        {
            setBuffer(map + 1);
            cur = first;
        }
        return *this;
    }
    template <class T, size_t BufSize>
    typename dequeIterator<T, BufSize>::iterator dequeIterator<T, BufSize>::operator++(int)
    {
        auto temp = *this;
        ++*this;
        return temp;
    }
    template <class T, size_t BufSize>
    typename dequeIterator<T, BufSize>::iterator& dequeIterator<T, BufSize>::operator--()
    {
        if (cur == first)
        {
            setBuffer(map - 1);
            cur = last;
        }
        --cur;
        return *this;
    }
    template <class T, size_t BufSize>
    typename dequeIterator<T, BufSize>::iterator dequeIterator<T, BufSize>::operator--(int)
    {
        auto temp = *this;
        --*this;
        return temp;
    }
    template <class T, size_t BufSize>
    typename dequeIterator<T, BufSize>::iterator&
    dequeIterator<T, BufSize>::operator+=(difference_type n)
    {
        difference_type offset = n + cur - first;
        difference_type bufsize = (difference_type)bufferSize();
        if (offset >= 0 && offset < bufsize)
        {
            cur += n;
        }
        else
        {
            difference_type map_offset =
                offset > 0 ? offset / bufsize : -((-offset - 1) / bufsize) - 1;
            setBuffer(map + map_offset);
            cur = first + offset - map_offset * bufsize;
        }
        return *this;
    }
    template <class T, size_t BufSize>
    typename dequeIterator<T, BufSize>::iterator
    dequeIterator<T, BufSize>::operator+(difference_type n)
    {
        auto temp = *this;
        return temp += n;
    }
    template <class T, size_t BufSize>
    typename dequeIterator<T, BufSize>::iterator&
    dequeIterator<T, BufSize>::operator-=(difference_type n)
    {
        auto temp = *this;
        return temp += (-n);
    }
    template <class T, size_t BufSize>
    typename dequeIterator<T, BufSize>::iterator
    dequeIterator<T, BufSize>::operator-(difference_type n)
    {
        auto temp = *this;
        return temp -= n;
    }
}  // namespace mySTL


namespace mySTL
{
    template <class T, class Alloc = Allocator<T>, size_t BufSize = 0>
    class deque
    {
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
        iterator start;
        iterator finish;
        map_pointer map;
        size_type map_size;

    public:
        deque();
        explicit deque(size_type n, const T& val);
        ~deque();

    public:
        iterator begin() { return start; }
        iterator end() { return finish; }
        const_iterator begin() const { return start; }
        const_iterator end() const { return finish; }

        reference front() { return *start; }
        reference back() { return *(--end()); }

        size_type size() { return finish - start; }
        bool empty() { return finish == start; }

    private:
        void createMap(size_type elems);
        void fillMap(size_type n, const T& val);
        void reallocateMap();
        void deallocateAll();

        size_type bufferSize() { return getDequeBufferSize(BufSize, sizeof(T)); }
        size_type getMapSize(size_type n) { return n == 0 ? 2 : n * 2; }

    public:
        void push_back(const T& val);
        void push_front(const T& val);
        void pop_back();
        void pop_front();
        void clear();
    };
}  // namespace mySTL

namespace mySTL
{

    template <class T, class Alloc, size_t BufSize>
    deque<T, Alloc, BufSize>::deque() : start(),
                                        finish(),
                                        map(nullptr),
                                        map_size(0)
    {
        createMap(bufferSize());
    }
    template <class T, class Alloc, size_t BufSize>
    deque<T, Alloc, BufSize>::deque(size_type n, const T& val)
        : start(),
          finish(),
          map(nullptr),
          map_size(0)
    {
        createMap(n);
        fillMap(n, val);
    }

    template <class T, class Alloc, size_t BufSize>
    deque<T, Alloc, BufSize>::~deque()
    {
        deallocateAll();
    }

    template <class T, class Alloc, size_t BufSize>
    void deque<T, Alloc, BufSize>::push_back(const T& val)
    {
        if (map[map_size - 1] && finish.cur == map[map_size])
        {  //满了
            reallocateMap();
        }
        data_allocator::construct(finish.cur, val);
        ++finish;
    }

    template <class T, class Alloc, size_t BufSize>
    void deque<T, Alloc, BufSize>::push_front(const T& val)
    {
        if (map[0] && start.cur == map[0])
        {  //满了
            reallocateMap();
        }
        --start;
        data_allocator::construct(start.cur, val);
    }

    template <class T, class Alloc, size_t BufSize>
    void deque<T, Alloc, BufSize>::pop_back()
    {
        --finish;
        data_allocator::destroy(finish.cur);
    }

    template <class T, class Alloc, size_t BufSize>
    void deque<T, Alloc, BufSize>::pop_front()
    {
        data_allocator::destroy(start.cur);
        ++start;
    }

    template <class T, class Alloc, size_t BufSize>
    void deque<T, Alloc, BufSize>::clear()
    {
        auto bufs = bufferSize();
        for (size_t i = 0; i < map_size; ++i)
        {
            for (auto ptr = map[i]; ptr != map[i] + bufs && ptr; ++ptr)
            {
                data_allocator::destroy(ptr);
            }
        }
        start.setBuffer(map + map_size / 2);
        finish.setBuffer(map + map_size / 2);
        start.cur = finish.cur = start.first;
    }

    template <class T, class Alloc, size_t BufSize>
    void deque<T, Alloc, BufSize>::createMap(size_type elems)
    {
        size_type bufs = getDequeBufferSize(BufSize, sizeof(T));
        size_type maps = elems / bufs + 1;
        map_size = getMapSize(maps);
        map = map_allocator::allocate(map_size);

        for (map_pointer cur = map; cur < map + map_size; ++cur)
        {
            *cur = data_allocator::allocate(bufs);
        }
        start.setBuffer(map + map_size / 2);
        finish.setBuffer(map + map_size / 2);
        start.cur = start.first;
        finish.cur = finish.first;
    }

    template <class T, class Alloc, size_t BufSize>
    void deque<T, Alloc, BufSize>::fillMap(size_type n, const T& val)
    {
        for (size_type i = 0; i < n / 2; ++i)
        {
            push_back(val);
        }
        for (size_type i = n / 2; i < n; ++i)
        {
            push_front(val);
        }
    }

    template <class T, class Alloc, size_t BufSize>
    void deque<T, Alloc, BufSize>::reallocateMap()
    {
        size_type new_size = getMapSize(map_size);
        map_pointer new_map = map_allocator::allocate(new_size);
        size_type bufs = bufferSize();

        for (size_type i = 0; i < new_size; ++i)
        {
            new_map[i] = data_allocator::allocate(bufs);
        }

        for (size_type i = 0; i < map_size; ++i)
        {
            for (size_type j = 0; j < bufs; ++j)
            {
                new_map[i + new_size / 4][j] = map[i][j];
            }
        }

        iterator mid;
        mid.setBuffer(map + map_size / 2);
        mid.cur = mid.first;
        iterator new_mid;
        new_mid.setBuffer(new_map + new_size / 2);
        new_mid.cur = new_mid.first;
        auto dis = mid - start;
        iterator new_start = new_mid - dis;
        dis = finish - mid;
        iterator new_finish = new_mid + dis;
        deallocateAll();
        map = new_map;
        map_size = new_size;
        start = new_start;
        finish = new_finish;
    }

    template <class T, class Alloc, size_t BufSize>
    void deque<T, Alloc, BufSize>::deallocateAll()
    {
        auto bufs = bufferSize();
        for (size_t i = 0; i < map_size; ++i)
        {
            for (auto ptr = map[i]; ptr < map[i] + bufs && ptr; ++ptr)
            {
                data_allocator::destroy(ptr);
            }
            if (map[i])
                data_allocator::deallocate(map[i], bufs);
        }
        map_allocator::deallocate(map, map_size);
    }

}  // namespace mySTL

#endif