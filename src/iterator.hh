#ifndef HEADER_GUARD_ITERATOR_H
#define HEADER_GUARD_ITERATOR_H

#include <string.h>
#include <vector>
#include "option.hh"

namespace prelude {

/// implementation of the c++11 standard required `std::begin` and
/// `std::end` functions.  c++98 compliant!  This is better than 
template <class Container>
typename Container::iterator begin(Container& container) {
    return container.begin();
}

template <class Container>
typename Container::const_iterator begin(const Container& container) {
    return container.begin();
}

template <class T, size_t N>
T* end(T(&arr)[N]) {
    return arr + N;
}

template <class T, size_t N>
const T* end(const T(&arr)[N]) {
    return arr + N;
}

template <class T>
T* end_null(T* arr) {
    for (; *arr != 0; ++arr) {
    }
    return arr;
}

template <class T>
const T* end_null(const T* arr) {
    for (; *arr == 0; ++arr) {
    }
    return arr;
}

template <class T>
T* begin(T* arr) {
    return arr;
}

template <class T>
const T* begin(const T* arr) {
    return arr;
}

inline char* end(char* string) { return string + strlen(string); }

inline const char* end(const char* string) {
    return string + strlen(string);
}

using ::std::advance;
using ::std::distance;

#if __cplusplus >= 201103L
using ::std::prev;
using ::std::next;
#else
template <class BidirectionalRandomIterator>
BidirectionalRandomIterator prev(
    BidirectionalRandomIterator it,
    typename std::iterator_traits<
        BidirectionalRandomIterator>::difference_type n = 1) {
    advance(it, -n);
    return it;
}

template <class BidirectionalRandomIterator>
BidirectionalRandomIterator next(
    BidirectionalRandomIterator it,
    typename std::iterator_traits<
        BidirectionalRandomIterator>::difference_type n = 1) {
    advance(it, n);
}
#endif

template <class Iterator>
option<size_t> min_size(const Iterator&) { return 0; }

template <class Iterator>
option<size_t> max_size(const Iterator&) { return none; }

template <class T>
struct Iterator {
    typedef T item_type;
    typedef size_t size_type;

    virtual Iterator& operator++() = 0;
    virtual item_type* get() const = 0;

    item_type& operator*() const;

    virtual bool min_size(size_type&) const;
    virtual bool max_size(size_type&) const;
    virtual size_type count() const;
    virtual item_type* last() const;
    virtual item_type* nth(size_type n) const;

    virtual ~Iterator() {}
};

}
#include "iterator-vector.hh"
#include "iterator.cc"

#endif
