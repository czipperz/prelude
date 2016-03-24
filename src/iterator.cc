#ifndef HEADER_GUARD_ITERATOR_C
#define HEADER_GUARD_ITERATOR_C

#include "iterator.hh"

namespace prelude {

template <class T>
typename Iterator<T>::item_type& Iterator<T>::operator*() const {
    return *get();
}

template <class T>
bool Iterator<T>::min_size(size_type& out) const {
    out = 0;
    return true;
}

template <class T>
bool Iterator<T>::max_size(size_type&) const {
    return false;
}

template <class T>
typename Iterator<T>::size_type Iterator<T>::count() const {
    Iterator<T>::size_type count = 0;
    for (; this->get(); ++count) {
        ++*this;
    }
    return count;
}

template <class T>
typename Iterator<T>::item_type* Iterator<T>::last() const {
    Iterator<T>::item_type* t = this->get();
    while (t) {
        t = (++*this).get();
    }
    return t;
}

template <class T>
typename Iterator<T>::item_type* Iterator<T>::nth(Iterator<T>::size_type n) const {
    for (; this->get(); ++*this) {
        if (n == 0) {
            return this->get();
        }
        --n;
    }
    return NULL;
}

}

#endif
