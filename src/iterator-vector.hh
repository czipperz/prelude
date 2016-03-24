#if 0
#ifndef HEADER_GUARD_VECTOR_H
#define HEADER_GUARD_VECTOR_H

#include "iterator.hh"

namespace prelude {

template <class T, class Iter = typename std::vector<T>::iterator >
struct VectorIterator : public Iterator<T> {
    typedef Iter iterator;
    typedef typename Iterator<T>::size_type size_type;
    typedef typename Iterator<T>::item_type item_type;

#if __cplusplus < 201103L
#  define override
#endif

    VectorIterator& operator++() override;
    item_type* get() const override;

    bool min_size(size_type&) const override;
    bool max_size(size_type&) const override;
    size_type count() override;
    item_type* last() override;
    item_type* nth(size_type n) override;

    ~VectorIterator() override {}

#undef override

private:
    template <class U>
    friend VectorIterator<U> iterator(std::vector<U>&);
    // friend VectorIterator<const T> iterator(const std::vector<T>&);
    VectorIterator(iterator begin, iterator end)
        : iter(begin), end(end) {}

    iterator iter;
    iterator end;
};

// template <class T>
// using ConstVectorIterator =
//     VectorIterator<T, typename std::vector<T>::const_iterator>;

template <class T>
VectorIterator<T> iterator(std::vector<T>& vector) {
    return VectorIterator<T>(vector.begin(), vector.end());
}

// template <class T>
// ConstVectorIterator<const T> iterator(const std::vector<T>& vector) {
//     return ConstVectorIterator<const T>(vector.begin(), vector.end());
// }

}

#include "iterator-vector.cc"

#endif
#endif
