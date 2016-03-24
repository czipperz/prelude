#if 0
#ifndef HEADER_GUARD_VECTOR_C
#define HEADER_GUARD_VECTOR_C

#include "iterator-vector.hh"

#if __cplusplus < 201103L
#define nullptr NULL
#endif

namespace prelude {

template <class T, class Iter>
VectorIterator<T, Iter>& VectorIterator<T, Iter>::operator++() {
    ++iter;
    return *this;
}

template <class T, class Iter>
typename VectorIterator<T, Iter>::item_type*
VectorIterator<T, Iter>::get() const {
    if (iter >= end) {
        return nullptr;
    } else {
        return &*iter;
    }
}

template <class T, class Iter>
bool VectorIterator<T, Iter>::min_size(size_type& st) const {
    st = end - iter;
    return true;
}

template <class T, class Iter>
bool VectorIterator<T, Iter>::max_size(size_type& st) const {
    return min_size(st);
}

template <class T, class Iter>
typename VectorIterator<T, Iter>::size_type
VectorIterator<T, Iter>::count() {
    VectorIterator<T, Iter>::size_type st = end - iter;
    iter = end;
    return st;
}

template <class T, class Iter>
typename VectorIterator<T, Iter>::item_type*
VectorIterator<T, Iter>::last() {
    if (iter >= end) {
        iter = end;
        return nullptr;
    } else {
        iter = end;
        return &*(end - 1);
    }
}

template <class T, class Iter>
typename VectorIterator<T, Iter>::item_type*
VectorIterator<T, Iter>::nth(size_type n) {
    if (iter + n >= end) {
        iter = end;
        return nullptr;
    } else {
        return &*(iter += n);
    }
}
}

#endif
#endif
