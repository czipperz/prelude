#ifndef HEADER_GUARD_ALGORITHM_H
#define HEADER_GUARD_ALGORITHM_H

#include <assert.h>
#include <algorithm>
#include <iterator>
#include "iterator.hh"
#include <memory>
#include "metaprogramming.hh"
#include "type_traits.hh"

namespace prelude {

#if __cplusplus >= 201103L
#define IF_CPLUSPLUS_11(t, f) t
#else
#define IF_CPLUSPLUS_11(t, f) f
#endif

#if __cplusplus >= 201103L
using ::std::forward;
#else
// never converts to rvalue types as those don't exist on this
// compiler.
template <class T>
T& forward(typename remove_const<
           typename remove_reference<T>::type>::type& arg) {
    return arg;
}
template <class T>
const T& forward(const typename remove_const<
                 typename remove_reference<T>::type>::type& arg) {
    return arg;
}
#endif

#if __cplusplus >= 201103L
using ::std::move;
#else
template <class T>
// this doesn't work as expected (!) but it does make the code more
// understandable.
T& move(typename remove_const<
           typename remove_reference<T>::type>::type& arg) {
    return arg;
}
template <class T>
const T& move(const typename remove_const<
                 typename remove_reference<T>::type>::type& arg) {
    return arg;
}
#endif

// <algorithm>'s algorithms are differing based on release date
// also allows for move semantics and std::begin.
#if __cplusplus >= 201103L

using ::std::all_of;
using ::std::any_of;
using ::std::none_of;

#else

template <class InputIterator, class UnaryPredicate>
bool all_of(InputIterator first, InputIterator last,
            UnaryPredicate pred) {
    while (first != last) {
        if (not pred(*first)) {
            return false;
        }
        ++first;
    }
    return true;
}

template <class InputIterator, class UnaryPredicate>
bool any_of(InputIterator first, InputIterator last,
            UnaryPredicate pred) {
    while (first != last) {
        if (pred(*first)) {
            return true;
        }
        ++first;
    }
    return false;
}

template <class InputIterator, class UnaryPredicate>
bool none_of(InputIterator first, InputIterator last,
             UnaryPredicate pred) {
    while (first != last) {
        if (pred(*first)) {
            return false;
        }
        ++first;
    }
    return true;
}

#endif

template <class Container, class UnaryPredicate>
bool all_of(const Container& container,
            UnaryPredicate IF_CPLUSPLUS_11(&&, ) pred) {
    return all_of(begin(container), end(container), pred);
}

template <class Container, class UnaryPredicate>
bool any_of(const Container& container,
            UnaryPredicate IF_CPLUSPLUS_11(&&, ) pred) {
    return any_of(begin(container), end(container), pred);
}

template <class Container, class UnaryPredicate>
bool none_of(const Container& container,
             UnaryPredicate IF_CPLUSPLUS_11(&&, ) pred) {
    return none_of(begin(container), end(container), pred);
}

using ::std::for_each;

template <class Container, class UnaryFunction>
UnaryFunction for_each(Container& container, UnaryFunction fn) {
    return for_each(begin(container), end(container), fn);
}

using ::std::find;

template <class Container, class T>
IF_CPLUSPLUS_11(auto, typename iterator_type_of<Container>::type)
find(const Container& container, const T& val)
#if __cplusplus >= 201103L
    -> decltype(find(begin(container), end(container),
                     forward<T>(val)))
#endif
{
    return find(begin(container), end(container), val);
}

// template <class Container, class T>
// typename Container::const_iterator find(const Container& container,
// const T& val) {
//     return find(begin(container),
//                 end(container),
//                 val);
// }

using ::std::find_if;

template <class Container, class UnaryPredicate>
IF_CPLUSPLUS_11(auto, typename iterator_type_of<Container>::type)
find_if(const Container& container, UnaryPredicate pred)
#if __cplusplus >= 201103L
    -> decltype(find_if(begin(container), end(container), pred))
#endif
{
    return find_if(begin(container), end(container), pred);
}

#if __cplusplus >= 201103L

using ::std::find_if_not;

#else

template <class InputIterator, class UnaryPredicate>
InputIterator find_if_not(InputIterator first, InputIterator last,
                          UnaryPredicate pred) {
    while (first != last) {
        if (not pred(*first)) {
            return first;
        }
        ++first;
    }
    return last;
}

#endif

template <class Container, class UnaryPredicate>
IF_CPLUSPLUS_11(auto, typename iterator_type_of<Container>::type)
find_if_not(Container& container, UnaryPredicate pred)
#if __cplusplus >= 201103L
    -> decltype(find_if_not(begin(container), end(container), pred))
#endif
{
    return find_if_not(begin(container), end(container), pred);
}

using ::std::find_end;

template <class Container1, class Container2>
IF_CPLUSPLUS_11(auto, typename iterator_type_of<Container1>::type)
find_end(const Container1& container1, const Container2& container2)
#if __cplusplus >= 201103L
    -> decltype(std::find_end(begin(container1), end(container1),
                              begin(container2), end(container2)))
#endif
{
    return std::find_end(begin(container1), end(container1),
                         begin(container2), end(container2));
}

template <class Container1, class Container2, class BinaryPredicate>
IF_CPLUSPLUS_11(auto, typename iterator_type_of<Container1>::type)
find_end(const Container1& container1, const Container2& container2,
         BinaryPredicate pred)
#if __cplusplus >= 201103L
    -> decltype(std::find_end(begin(container1), end(container1),
                              begin(container2), end(container2),
                              pred))
#endif
{
    return std::find_end(begin(container1), end(container1),
                         begin(container2), end(container2), pred);
}

using ::std::find_first_of;

template <class Container1, class Container2>
IF_CPLUSPLUS_11(auto, typename iterator_type_of<Container1>::type)
find_first_of(const Container1& container1,
              const Container2& container2)
#if __cplusplus >= 201103L
    -> decltype(std::find_first_of(begin(container1), end(container1),
                                   begin(container2),
                                   end(container2)))
#endif
{
    return std::find_first_of(begin(container1), end(container1),
                              begin(container2), end(container2));
}

template <class Container1, class Container2, class BinaryPredicate>
IF_CPLUSPLUS_11(auto, typename iterator_type_of<Container1>::type)
find_first_of(const Container1& container1,
              const Container2& container2, BinaryPredicate pred)
#if __cplusplus >= 201103L
    -> decltype(std::find_first_of(begin(container1), end(container1),
                                   begin(container2), end(container2),
                                   pred))
#endif
{
    return std::find_first_of(begin(container1), end(container1),
                              begin(container2), end(container2),
                              pred);
}

using ::std::adjacent_find;

template <class Container>
IF_CPLUSPLUS_11(auto, typename iterator_type_of<Container>::type)
adjacent_find(const Container& container)
#if __cplusplus >= 201103L
    -> decltype(std::adjacent_find(begin(container), end(container)))
#endif
{
    return std::adjacent_find(begin(container), end(container));
}

template <class Container, class BinaryPredicate>
IF_CPLUSPLUS_11(auto, typename iterator_type_of<Container>::type)
adjacent_find(const Container& container, BinaryPredicate pred)
#if __cplusplus >= 201103L
    -> decltype(std::adjacent_find(begin(container), end(container),
                                   pred))
#endif
{
    return std::adjacent_find(begin(container), end(container), pred);
}

using ::std::count;

template <class Container, class T>
IF_CPLUSPLUS_11(auto, typename iterator_type_of<Container>::type)
count(const Container& container, const T& val)
#if __cplusplus >= 201103L
    -> decltype(std::count(begin(container), end(container),
                           forward<T>(val)))
#endif
{
    return std::count(begin(container), end(container),
                      forward<T>(val));
}

using ::std::count_if;

template <class Container, class UnaryPredicate>
IF_CPLUSPLUS_11(auto, typename iterator_type_of<Container>::type)
count_if(const Container& container, UnaryPredicate pred)
#if __cplusplus >= 201103L
    -> decltype(std::count_if(begin(container), end(container), pred))
#endif
{
    return std::count_if(begin(container), end(container), pred);
}

using ::std::mismatch;

template <class Container1, class Container2>
#define PAIR(a, b) std::pair<a, b>
IF_CPLUSPLUS_11(auto,
                PAIR(typename iterator_type_of<Container1>::type,
                     typename iterator_type_of<Container2>::type))
mismatch(const Container1& container1, const Container2& container2)
#if __cplusplus >= 201103L
    -> decltype(std::mismatch(begin(container1), end(container1),
                              begin(container2)))
#endif
{
    return std::mismatch(begin(container1), end(container1),
                         begin(container2));
}

// move
template <class Container1, class Container2, class BinaryPredicate>
IF_CPLUSPLUS_11(auto,
                PAIR(typename iterator_type_of<Container1>::type,
                     typename iterator_type_of<Container2>::type))
mismatch(const Container1& container1, const Container2& container2,
         BinaryPredicate pred)
#undef PAIR
#if __cplusplus >= 201103L
    -> decltype(std::mismatch(begin(container1), end(container1),
                              begin(container2), pred))
#endif
{
    return std::mismatch(begin(container1), end(container1),
                         begin(container2), pred);
}

using ::std::equal;

template <class Container1, class Container2>
bool equal(const Container1& container1,
           const Container2& container2) {
    return std::equal(begin(container1), end(container1),
                      begin(container2));
}

template <class Container1, class Container2, class BinaryPredicate>
bool equal(const Container1& container1, const Container2& container2,
           BinaryPredicate pred) {
    return std::equal(begin(container1), end(container1),
                      begin(container2), pred);
}

#if __cplusplus >= 201103L
using ::std::is_permutation;
#else
template <class InputIterator1, class InputIterator2>
bool is_permutation(InputIterator1 first1, InputIterator1 last1,
                    InputIterator2 first2) {
    std::pair<InputIterator1, InputIterator2> pair =
        mismatch(first1, last1, first2);
    first1 = pair.first;
    first2 = pair.second;
    if (first1 == first2)
        return true;
    InputIterator2 last2 = first2;
    advance(last2, distance(first1, last1));
    for (InputIterator1 it1 = first1; it1 != last1; ++it1) {
        if (find(first1, it1, *it1) == it1) {
            typename std::iterator_traits<
                InputIterator2>::difference_type n =
                count(first2, last2, *it1);
            if (n == 0 || count(it1, last1, *it1) != n) {
                return false;
            }
        }
    }
}
#endif

template <class Container1, class Container2>
bool is_permutation(const Container1& container1,
                    const Container2& container2) {
    return is_permutation(begin(container1), end(container1),
                          begin(container2));
}

template <class Container1, class Container2, class BinaryPredicate>
bool is_permutation(const Container1& container1,
                    const Container2& container2,
                    BinaryPredicate pred) {
    return is_permutation(begin(container1), end(container1),
                          begin(container2), pred);
}

using ::std::search;

template <class Container1, class Container2>
IF_CPLUSPLUS_11(auto, typename iterator_type_of<Container1>::type)
search(Container1& container1, const Container2& container2)
#if __cplusplus >= 201103L
    -> decltype(std::search(begin(container1), end(container1),
                            begin(container2), end(container2)))
#endif
{
    return std::search(begin(container1), end(container1),
                       begin(container2), end(container2));
}

template <class Container1, class Container2, class BinaryPredicate>
IF_CPLUSPLUS_11(auto, typename iterator_type_of<Container1>::type)
search(Container1& container1, const Container2& container2,
       BinaryPredicate pred)
#if __cplusplus >= 201103L
    -> decltype(std::search(begin(container1), end(container1),
                            begin(container2), end(container2), pred))
#endif
{
    return std::search(begin(container1), end(container1),
                       begin(container2), end(container2), pred);
}

using ::std::search_n;

template <class Container, class Size, class T>
IF_CPLUSPLUS_11(auto, typename iterator_type_of<Container>::type)
search_n(Container& container, Size count,
         IF_CPLUSPLUS_11(T&&, const T&) val)
#if __cplusplus >= 201103L
    -> decltype(std::search_n(begin(container), end(container), count,
                              forward<T>(val)))
#endif
{
    return std::search_n(begin(container), end(container), count,
                         forward<T>(val));
}

template <class Container, class Size, class T, class BinaryPredicate>
IF_CPLUSPLUS_11(auto, typename iterator_type_of<Container>::type)
search_n(Container& container, Size count,
         IF_CPLUSPLUS_11(T&&, const T&) val, BinaryPredicate pred)
#if __cplusplus >= 201103L
    -> decltype(std::search_n(begin(container), end(container), count,
                              forward<T>(val), pred))
#endif
{
    return std::search_n(begin(container), end(container), count,
                         forward<T>(val),
                         pred);
}

using ::std::copy;

template <class Container, class OutputIterator>
OutputIterator copy(const Container& container,
                    OutputIterator output) {
    return std::copy(begin(container), end(container), output);
}

#if __cplusplus >= 201103L
using ::std::copy_n;
using ::std::copy_if;
#else

template <class InputIterator, class Size, class OutputIterator>
OutputIterator copy_n(InputIterator first, Size n,
                      OutputIterator result) {
    while (n > 0) {
        *result = *first;
        ++result;
        ++first;
        --n;
    }
    return result;
}

template <class InputIterator, class OutputIterator,
          class UnaryPredicate>
OutputIterator copy_if(InputIterator first, InputIterator last,
                       OutputIterator output, UnaryPredicate pred) {
    while (first != last) {
        if (pred(*first)) {
            *output = *first;
            ++output;
        }
        ++first;
    }
    return output;
}

#endif

template <class Container, class Size, class OutputIterator>
OutputIterator copy_n(const Container& container, Size n,
                      OutputIterator output) {
    return copy_n(begin(container), n, output);
}

template <class Container, class OutputIterator, class UnaryPredicate>
OutputIterator copy_if(const Container& container,
                       OutputIterator output, UnaryPredicate pred) {
    return copy_if(begin(container), end(container), output, pred);
}

using ::std::copy_backward;

template <class BidirectionalContainer1,
          class BidirectionalOutputIterator>
BidirectionalOutputIterator copy_backward(
    const BidirectionalContainer1& container1,
    BidirectionalOutputIterator output) {
    return std::copy_backward(begin(container1), end(container1),
                              output);
}

#if __cplusplus >= 201103L
template <class InputIterator, class OutputIterator>
OutputIterator move(InputIterator first, InputIterator last,
                    OutputIterator output) {
    return std::move(first, last, output);
}

template <class Container, class OutputIterator>
OutputIterator move(Container&& container, OutputIterator output) {
    return std::move(begin(container), end(container), output);
}

template <class BidirectionalInputIterator,
          class BidirectionalOutputIterator>
BidirectionalOutputIterator move_backward(
    BidirectionalInputIterator first, BidirectionalInputIterator last,
    BidirectionalOutputIterator output) {
    return std::move_backward(first, last, output);
}

template <class BidirectionalContainer,
          class BidirectionalOutputIterator>
BidirectionalOutputIterator move_backward(
    BidirectionalContainer&& container,
    BidirectionalOutputIterator output) {
    return std::move_backward(begin(container), end(container),
                              output);
}
#endif

using ::std::swap_ranges;

template <class Container1, class Iterator>
Iterator swap_ranges_i(Container1& container1, Iterator first2) {
    return std::swap_ranges(begin(container1), end(container1),
                            first2);
}

template <class Container1, class Container2>
IF_CPLUSPLUS_11(auto, typename iterator_type_of<Container2>::type)
swap_ranges(Container1& container1, Container2& container2)
#if __cplusplus >= 201103L
    -> decltype(std::swap_ranges(begin(container1), end(container1),
                                 begin(container2)))
#endif
{
    return std::swap_ranges(begin(container1), end(container1),
                            begin(container2));
}

using ::std::transform;

template <class Container, class OutputIterator, class UnaryFunction>
OutputIterator transform(const Container& container,
                         UnaryFunction fn) {
    Container result;
    std::transform(begin(container), end(container),
                   std::back_inserter(result), fn);
    return result;
}

template <class Container, class OutputIterator, class BinaryFunction>
Container transform_binary(const Container& container1,
                           const Container& container2,
                           BinaryFunction fn) {
    Container result;
    std::transform(begin(container1), end(container1),
                   begin(container2), std::back_inserter(result), fn);
    return result;
}

template <class Container, class OutputIterator, class UnaryFunction>
OutputIterator transform(const Container& container,
                         OutputIterator output, UnaryFunction fn) {
    return std::transform(begin(container), end(container), output,
                          fn);
}

template <class Container1, class Container2, class OutputIterator,
          class BinaryFunction>
OutputIterator transform_binary(const Container1& container1,
                                const Container2& container2,
                                OutputIterator output,
                                BinaryFunction fn) {
    return std::transform(begin(container1), end(container1),
                          begin(container2), output, fn);
}

using ::std::replace;

template <class Container, class T>
void replace(Container& container,
             IF_CPLUSPLUS_11(T&&, const T&) old_value,
             IF_CPLUSPLUS_11(T&&, const T&) new_value) {
    return std::replace(begin(container), end(container),
                        forward<T>(old_value),
                        forward<T>(new_value));
}

using ::std::replace_if;

template <class Container, class UnaryPredicate, class T>
void replace_if(Container& container, UnaryPredicate pred,
                const T& new_value) {
    return std::replace_if(begin(container), end(container), pred,
                           forward<T>(new_value));
}

using ::std::replace_copy;

template <class Container, class OutputIterator, class T>
OutputIterator replace_copy(const Container& container,
                            OutputIterator result, const T& old_value,
                            const T& new_value) {
    return std::replace_copy(begin(container), end(container), result,
                             forward<T>(old_value),
                             forward<T>(new_value));
}

using ::std::replace_copy_if;

template <class Container, class OutputIterator, class UnaryPredicate,
          class T>
OutputIterator replace_copy_if(const Container& container,
                               OutputIterator result,
                               UnaryPredicate pred, const T& value) {
    return std::replace_copy_if(begin(container), end(container),
                                result, pred,
                                forward<T>(value));
}

using ::std::fill;

template <class Container, class T>
void fill(Container& container, IF_CPLUSPLUS_11(T&&, const T&) val) {
    return std::fill(begin(container), end(container),
                     forward<T>(val));
}

using ::std::fill_n;

using ::std::generate;

template <class Container, class Generator>
void generate(Container& container, Generator gen) {
    return std::generate(begin(container), end(container), gen);
}

using ::std::generate_n;

using ::std::remove;

template <class Container, class T>
void remove(Container& container, const T& val) {
    IF_CPLUSPLUS_11(auto, typename iterator_type_of<Container>::type)
    it = std::remove(begin(container), end(container),
                     forward<T>(val));
    if (it != end(container)) {
        container.erase(it, end(container));
    }
}

using ::std::remove_if;

template <class Container, class UnaryPredicate>
void remove_if(Container& container, UnaryPredicate pred) {
    IF_CPLUSPLUS_11(auto, typename iterator_type_of<Container>::type)
    it = std::remove_if(begin(container), end(container), pred);
    if (it != end(container)) {
        container.erase(it, end(container));
    }
}

using ::std::remove_copy;

template <class Container, class OutputIterator, class T>
OutputIterator remove_copy(const Container& container,
                           OutputIterator output, const T& val) {
    return std::remove_copy(begin(container), end(container), output,
                            forward<T>(val));
}

template <class Container, class T>
Container remove_copy(const Container& container, const T& val) {
    Container result;
    remove_copy(container, std::back_inserter(result), val);
    return result;
}

using ::std::remove_copy_if;

template <class Container, class OutputIterator, class UnaryPredicate>
OutputIterator remove_copy_if(const Container& container,
                              OutputIterator result,
                              UnaryPredicate pred) {
    return std::remove_copy_if(begin(container), end(container),
                               result, pred);
}

template <class Container, class UnaryPredicate>
Container remove_copy_if(const Container& container,
                         UnaryPredicate pred) {
    Container result;
    remove_copy_if(container, std::back_inserter(result), pred);
    return result;
}

template <class Container>
void unique(Container& container) {
    IF_CPLUSPLUS_11(auto, typename iterator_type_of<Container>::type)
    it = std::unique(begin(container), end(container));
    if (it != end(container)) {
        container.erase(it, end(container));
    }
}

template <class Container, class BinaryPredicate>
void unique_with(Container& container, BinaryPredicate pred) {
    IF_CPLUSPLUS_11(auto, typename iterator_type_of<Container>::type)
    it = std::unique(begin(container), end(container), pred);
    if (it != end(container)) {
        container.erase(it, end(container));
    }
}

template <class ForwardIterator>
void unique(ForwardIterator first, ForwardIterator last) {
    return std::unique(first, last);
}

template <class ForwardIterator, class BinaryPredicate>
void unique_with(ForwardIterator first, ForwardIterator last, BinaryPredicate pred) {
    return std::unique(first, last, pred);
}

template <class Container>
Container unique_copy(const Container& container) {
    Container result;
    std::unique_copy(begin(container), end(container),
                     std::back_inserter(result));
    return result;
}

template <class Container, class BinaryPredicate>
Container unique_copy_with(const Container& container,
                           BinaryPredicate pred) {
    Container result;
    return std::unique_copy(begin(container), end(container),
                            std::back_inserter(result), pred);
    return result;
}

template <class Container>
Container unique_copy(typename iterator_type_of<Container>::type first,
                      typename iterator_type_of<Container>::type last) {
    Container result;
    std::unique_copy(first, last, std::back_inserter(result));
    return result;
}

template <class Container, class BinaryPredicate>
Container unique_copy_with(typename iterator_type_of<Container>::type first,
                           typename iterator_type_of<Container>::type last,
                           BinaryPredicate pred) {
    Container result;
    return std::unique_copy(first, last, std::back_inserter(result),
                            pred);
    return result;
}

template <class InputIterator, class OutputIterator>
OutputIterator unique_copy_out(InputIterator first,
                               InputIterator last,
                               OutputIterator result) {
    return std::unique_copy(first, last, result);
}

template <class InputIterator, class OutputIterator,
          class BinaryPredicate>
OutputIterator unique_copy_out_with(InputIterator first,
                                    InputIterator last,
                                    OutputIterator result,
                                    BinaryPredicate pred) {
    return std::unique_copy(first, last, result, pred);
}

template <class Container, class OutputIterator>
OutputIterator unique_copy_out(const Container& container,
                               OutputIterator output) {
    return std::unique_copy(begin(container), end(container), output);
}

template <class Container, class OutputIterator,
          class BinaryPredicate>
OutputIterator unique_copy_out_with(const Container& container,
                                    OutputIterator output,
                                    BinaryPredicate pred) {
    return std::unique_copy(begin(container), end(container), output,
                            pred);
}

using ::std::reverse;

template <class Container>
void reverse(Container& container) {
    return std::reverse(begin(container), end(container));
}

using ::std::reverse_copy;

template <class Container, class OutputIterator>
OutputIterator reverse_copy(Container& container,
                            OutputIterator output) {
    return std::reverse_copy(begin(container), end(container),
                             output);
}

template <class Container, class OutputIterator>
Container reverse_copy(const Container& container) {
    Container result;
    return std::reverse_copy(begin(container), end(container),
                             std::back_inserter(result));
    return result;
}

using ::std::rotate;

template <class Container, class ForwardIterator>
ForwardIterator rotate(Container& container,
                       ForwardIterator middle) {
    return std::rotate(begin(container), middle, end(container));
}

template <class ForwardIterator, class OutputIterator>
ForwardIterator rotate_copy_out(ForwardIterator first,
                                ForwardIterator middle,
                                ForwardIterator last,
                                OutputIterator output) {
    return std::rotate_copy(first, middle, last, output);
}

template <class Container, class ForwardIterator,
          class OutputIterator>
ForwardIterator rotate_copy_out(const Container& container,
                                ForwardIterator middle,
                                OutputIterator output) {
    return std::rotate_copy(begin(container), middle, end(container),
                            output);
}

template <class Container>
Container rotate_copy(
    typename iterator_type_of<Container>::type first,
    typename iterator_type_of<Container>::type middle,
    typename iterator_type_of<Container>::type last) {
    Container result;
    std::rotate_copy(first, middle, last, std::back_inserter(result));
    return result;
}

template <class Container, class ForwardIterator>
Container rotate_copy(const Container& container,
                      ForwardIterator middle) {
    Container result;
    std::rotate_copy(begin(container), middle, end(container),
                     std::back_inserter(result));
    return result;
}

template <class RandomAccessIterator>
void random_shuffle(RandomAccessIterator first, RandomAccessIterator last) {
    return std::random_shuffle(first, last);
}

template <class RandomAccessIterator, class RandomNumberGenerator>
void random_shuffle_generator(
    RandomAccessIterator first, RandomAccessIterator last,
    RandomNumberGenerator IF_CPLUSPLUS_11(&&, &) gen) {
    return std::random_shuffle(first, last,
                               forward<RandomNumberGenerator>(gen));
}

template <class Container>
void random_shuffle(Container& container) {
    return std::random_shuffle(begin(container), end(container));
}

template <class Container, class RandomNumberGenerator>
void random_shuffle_generator(
    Container& container,
    RandomNumberGenerator IF_CPLUSPLUS_11(&&, &) gen) {
    return std::random_shuffle(begin(container), end(container),
                               forward<RandomNumberGenerator>(gen));
}

#if __cplusplus >= 201103L
using ::std::shuffle;
#else
// at bottom of file
template <class NumType>
NumType transform_range(NumType val, NumType min_val, NumType max_val,
                        NumType min_result, NumType max_result);

template <class Container, class URNG>
void shuffle(typename iterator_type_of<Container>::type first,
             typename iterator_type_of<Container>::type last,
             URNG& g) {
    for (typename std::iterator_traits<Container>::difference_type i =
             (last - first) - 1;
         i > 0; --i) {
        swap(first[i], first[transform_range(g(), g.min(), g.max(),
                                             0, i)]);
    }
}
#endif

template <class Container, class URNG>
void shuffle(Container& container, URNG IF_CPLUSPLUS_11(&&,&) g) {
    return shuffle(begin(container), end(container),
                        forward<URNG>(g));
}

#if __cplusplus >= 201103L
using ::std::is_partitioned;
#else
template <class InputIterator, class UnaryPredicate>
bool is_partitioned(InputIterator first, InputIterator last, UnaryPredicate pred) {
    while (first != last and pred(*first)) {
        ++first;
    }
    while (first != last) {
        if (pred(*first)) {
            return false;
        }
        ++first;
    }
    return true;
}
#endif

template <class Container, class UnaryPredicate>
bool is_partitioned(const Container& container, UnaryPredicate pred) {
    return is_partitioned(begin(container), end(container),
                               pred);
}

using ::std::partition;

template <class Container, class UnaryPredicate>
IF_CPLUSPLUS_11(auto, typename iterator_type_of<Container>::type)
    partition(Container& container, UnaryPredicate pred)
    #if __cplusplus >= 201103L
    -> decltype(std::partition(begin(container), end(container),
                               pred))
    #endif
{
    return std::partition(begin(container), end(container), pred);
}

using ::std::stable_partition;

template <class Container, class UnaryPredicate>
IF_CPLUSPLUS_11(auto, typename iterator_type_of<Container>::type)
    stable_partition(Container& container, UnaryPredicate pred)
    #if __cplusplus >= 201103L
    -> decltype(std::stable_partition(begin(container),
                                      end(container), pred))
    #endif
{
    return std::stable_partition(begin(container), end(container),
                                 pred);
}

#if __cplusplus >= 201103L
using ::std::partition_copy;
#else
template <class InputIterator, class OutputIterator1,
          class OutputIterator2, class UnaryPredicate>
std::pair<OutputIterator1, OutputIterator2> partition_copy(
    InputIterator first, InputIterator last,
    OutputIterator1 output_true, OutputIterator2 output_false,
    UnaryPredicate pred) {
    while (first != last) {
        if (pred(*first)) {
            *output_true = *first;
            ++output_true;
        } else {
            *output_false = *first;
            ++output_false;
        }
        ++first;
    }
    return std::pair<OutputIterator1, OutputIterator2>(output_true,
                                                       output_false);
}
#endif

template <class Container, class OutputIterator1,
          class OutputIterator2, class UnaryPredicate>
std::pair<OutputIterator1, OutputIterator2> partition_copy(
    const Container& container, OutputIterator1 output_true,
    OutputIterator2 output_false, UnaryPredicate pred) {
    return partition_copy(begin(container), end(container),
                          output_true, output_false, pred);
}

template <class Container, class UnaryPredicate>
std::pair<Container, Container> partition_copy(
    const Container& container, UnaryPredicate pred) {
    Container res1, res2;
    partition_copy(begin(container), end(container),
                   std::back_inserter(res1), std::back_inserter(res2),
                   pred);
    return std::pair<Container, Container>(move(res1), move(res2));
}

template <class Container, class UnaryPredicate>
IF_CPLUSPLUS_11(auto, typename iterator_type_of<Container>::type)
partition_point(const Container& container, UnaryPredicate pred)
#if __cplusplus >= 201103L
    -> decltype(partition_point(begin(container), end(container),
                                pred))
#endif
{
    return partition_point(begin(container), end(container), pred);
}

template <class Container>
void sort(Container& container) {
    return std::sort(begin(container), end(container));
}

template <class Container, class Compare>
void sort_with(Container& container, Compare comp) {
    return std::sort(begin(container), end(container), comp);
}

template <class RandomAccessIterator>
void sort(RandomAccessIterator first, RandomAccessIterator last) {
    return std::sort(first, last);
}

template <class RandomAccessIterator, class Compare>
void sort_with(RandomAccessIterator first, RandomAccessIterator last,
               Compare comp) {
    return std::sort(first, last, comp);
}

template <class Container>
void stable_sort(Container& container) {
    return std::stable_sort(begin(container), end(container));
}

template <class Container, class Compare>
void stable_sort_with(Container& container, Compare comp) {
    return std::stable_sort(begin(container), end(container), comp);
}

template <class RandomAccessIterator>
void stable_sort(RandomAccessIterator first,
                 RandomAccessIterator last) {
    return std::stable_sort(first, last);
}

template <class RandomAccessIterator, class Compare>
void stable_sort_with(RandomAccessIterator first,
                      RandomAccessIterator last, Compare comp) {
    return std::stable_sort(first, last, comp);
}

template <class Container, class RandomAccessIterator>
void partial_sort(Container& container,
                  RandomAccessIterator middle) {
    return std::partial_sort(begin(container), middle,
                             end(container));
}

template <class Container, class RandomAccessIterator, class Compare>
void partial_sort_with(Container& container,
                       RandomAccessIterator middle, Compare comp) {
    return std::partial_sort(begin(container), middle, end(container),
                             comp);
}

template <class Container, class RandomAccessIterator>
void partial_sort(RandomAccessIterator first,
                  RandomAccessIterator middle,
                  RandomAccessIterator last) {
    return std::partial_sort(first, middle, last);
}

template <class Container, class RandomAccessIterator, class Compare>
void partial_sort_with(RandomAccessIterator first,
                       RandomAccessIterator middle,
                       RandomAccessIterator last, Compare comp) {
    return std::partial_sort(first, middle, last, comp);
}

template <class Container, class RandomAccessIterator>
Container partial_sort_copy(const Container& container, size_t n) {
    Container result;
    result.reserve(n);
    std::partial_sort_copy(begin(container), end(container),
                           begin(result),
                           next(begin(result), n));
    return result;
}

template <class Container, class Compare>
Container partial_sort_copy_with(const Container& container, size_t n,
                                 Compare comp) {
    Container result;
    result.reserve(n);
    std::partial_sort_copy(begin(container), end(container),
                           begin(result), next(begin(result), n),
                           comp);
    return result;
}

template <class Container, class RandomAccessIterator>
RandomAccessIterator partial_sort_copy(
    const Container& container, RandomAccessIterator output_first,
    RandomAccessIterator output_second) {
    return std::partial_sort_copy(begin(container), end(container),
                                  output_first, output_second);
}

// move
template <class Container, class RandomAccessIterator, class Compare>
RandomAccessIterator partial_sort_copy_with(
    const Container& container, RandomAccessIterator output_first,
    RandomAccessIterator output_second, Compare comp) {
    return std::partial_sort_copy(begin(container), end(container),
                                  output_first, output_second, comp);
}

#if __cplusplus >= 201103L
template <class Iterator>
bool is_sorted(Iterator first, Iterator last) {
    return ::std::is_sorted(first, last);
}

template <class Iterator, class Compare>
bool is_sorted_with(Iterator first, Iterator last, Compare comp) {
    return ::std::is_sorted(first, last, comp);
}
#else
template <class ForwardIterator>
bool is_sorted(ForwardIterator first, ForwardIterator last) {
    if (first == last) { return true; }
    ForwardIterator next = first;
    while (++next != last) {
        if (*next < *first) {
            return false;
        }
        ++first;
    }
    return true;
}

template <class ForwardIterator, class Compare>
bool is_sorted_with(ForwardIterator first, ForwardIterator last, Compare comp) {
    if (first == last) return true;
    ForwardIterator next = first;
    while (++next != last) {
        if (comp(*next, *first)) {
            return false;
        }
        ++first;
    }
    return true;
}
#endif

template <class Container>
bool is_sorted(const Container& container) {
    return is_sorted(begin(container), end(container));
}

template <class Container, class Compare>
bool is_sorted_with(const Container& container, Compare comp) {
    return is_sorted(begin(container), end(container), comp);
}

#if __cplusplus >= 201103L
template <class Iterator>
Iterator is_sorted_until(Iterator first, Iterator last) {
    return ::std::is_sorted_until(first, last);
}

template <class Iterator, class Compare>
Iterator is_sorted_until_with(Iterator first, Iterator last,
                              Compare comp) {
    return ::std::is_sorted_until(first, last, comp);
}
#else
template <class Iterator>
Iterator is_sorted_until(Iterator first, Iterator last) {
    if (first == last) {
        return first;
    }
    Iterator next = first;
    while (++next != last) {
        if (*next < *first) {
            return next;
        }
        ++first;
    }
    return last;
}

template <class Iterator, class Compare>
Iterator is_sorted_until_with(Iterator first, Iterator last,
                              Compare comp) {
    if (first == last) {
        return first;
    }
    Iterator next = first;
    while (++next != last) {
        if (comp(*next, *first)) {
            return next;
        }
        ++first;
    }
    return last;
}
#endif

template <class Container>
IF_CPLUSPLUS_11(auto, typename iterator_type_of<Container>::type)
    is_sorted_until(const Container& container)
    #if __cplusplus >= 201103L
    -> decltype(std::is_sorted_until(begin(container),
                                     end(container)))
    #endif
{
    return is_sorted_until(begin(container), end(container));
}

template <class Container, class Compare>
IF_CPLUSPLUS_11(auto, typename iterator_type_of<Container>::type)
    is_sorted_until_with(const Container& container, Compare comp)
    #if __cplusplus >= 201103L
    -> decltype(std::is_sorted_until(begin(container), end(container),
                                     comp))
    #endif
{
    return is_sorted_until_with(begin(container), end(container),
                                comp);
}

template <class Container, class Iterator>
void nth_element(Container& container, Iterator nth) {
    return std::nth_element(begin(container), nth, end(container));
}

template <class Container, class Iterator, class Compare>
void nth_element_with(Container& container, Iterator nth,
                      Compare comp) {
    return std::nth_element(begin(container), nth, end(container),
                            comp);
}

template <class Container, class Iterator>
void nth_element(Iterator first, Iterator nth, Iterator last) {
    return std::nth_element(first, nth, last);
}

template <class Container, class Iterator, class Compare>
void nth_element_with(Iterator first, Iterator nth, Iterator last,
                      Compare comp) {
    return std::nth_element(first, nth, last, comp);
}

template <class Container, class T>
IF_CPLUSPLUS_11(auto, typename iterator_type_of<Container>::type)
    lower_bound(Container& container, const T& val)
    #if __cplusplus >= 201103L
    -> decltype(std::lower_bound(begin(container), end(container),
                                 val))
    #endif
{
    return std::lower_bound(begin(container), end(container), val);
}

template <class Container, class T, class Compare>
IF_CPLUSPLUS_11(auto, typename iterator_type_of<Container>::type)
    lower_bound_with(Container& container, const T& val,
                      Compare comp)
    #if __cplusplus >= 201103L
    -> decltype(std::lower_bound(begin(container), end(container),
                                 val, comp))
    #endif
{
    return std::lower_bound(begin(container), end(container), val,
                            comp);
}

template <class Iterator, class T>
Iterator lower_bound(Iterator first, Iterator last, const T& val) {
    return std::lower_bound(first, last, val);
}

template <class Iterator, class T, class Compare>
Iterator lower_bound_with(Iterator first, Iterator last, const T& val,
                          Compare comp) {
    return std::lower_bound(first, last, val, comp);
}

template <class Container, class T>
IF_CPLUSPLUS_11(auto, typename iterator_type_of<Container>::type)
    upper_bound(Container& container, const T& val)
    #if __cplusplus >= 201103L
    -> decltype(std::upper_bound(begin(container), end(container),
                                 val))
    #endif
{
    return std::upper_bound(begin(container), end(container), val);
}

template <class Container, class T, class Compare>
IF_CPLUSPLUS_11(auto, typename iterator_type_of<Container>::type)
    upper_bound_with(Container& container, const T& val,
                      Compare comp)
    #if __cplusplus >= 201103L
    -> decltype(std::upper_bound(begin(container), end(container),
                                 val, comp))
    #endif
{
    return std::upper_bound(begin(container), end(container), val,
                            comp);
}

template <class Iterator, class T>
Iterator upper_bound(Iterator first, Iterator last, const T& val) {
    return std::upper_bound(first, last, val);
}

template <class Iterator, class T, class Compare>
Iterator upper_bound_with(Iterator first, Iterator last, const T& val,
                      Compare comp) {
    return std::upper_bound(first, last, val, comp);
}

template <class Container, class T>
#define PAIR(a) std::pair<a, a>
IF_CPLUSPLUS_11(auto, PAIR(typename iterator_type_of<Container>::type))
    equal_range(Container& container, const T& val)
    #if __cplusplus >= 201103L
    -> decltype(std::equal_range(begin(container), end(container),
                                 val))
    #endif
{
    return std::equal_range(begin(container), end(container), val);
}

template <class Container, class T, class Compare>
IF_CPLUSPLUS_11(auto, PAIR(typename iterator_type_of<Container>::type))
#undef PAIR
    equal_range_with(Container& container, const T& val,
                      Compare comp)
    #if __cplusplus >= 201103L
    -> decltype(std::equal_range(begin(container), end(container),
                                 val, comp))
    #endif
{
    return std::equal_range(begin(container), end(container), val,
                            comp);
}

template <class Iterator, class T>
std::pair<Iterator, Iterator>
equal_range(Iterator first, Iterator last, const T& val)
{
    return std::equal_range(first, last, val);
}

template <class Iterator, class T, class Compare>
std::pair<Iterator, Iterator>
equal_range_with(Iterator first, Iterator last, const T& val,
                      Compare comp) {
    return std::equal_range(first, last, val, comp);
}

template <class Container, class T>
bool binary_search(const Container& container, const T& val) {
    return std::binary_search(begin(container), end(container), val);
}

template <class Container, class T, class Compare>
bool binary_search_with(const Container& container, const T& val,
                        Compare comp) {
    return std::binary_search(begin(container), end(container), val,
                              comp);
}

template <class Iterator, class T>
bool binary_search(Iterator first, Iterator last, const T& val) {
    return std::binary_search(first, last, val);
}

template <class Iterator, class T, class Compare>
bool binary_search_with(Iterator first, Iterator last, const T& val,
                        Compare comp) {
    return std::binary_search(first, last, val, comp);
}

template <class Container1, class Container2, class OutputIterator>
OutputIterator merge(const Container1& container1, const Container2& container2,
                     OutputIterator output) {
    return std::merge(begin(container1), end(container1),
                      begin(container2), end(container2), output);
}

template <class Container1, class Container2, class OutputIterator,
          class Compare>
OutputIterator merge_with(const Container1& container1,
                          const Container2& container2,
                          OutputIterator output, Compare comp) {
    return std::merge(begin(container1), end(container1),
                      begin(container2), end(container2), output,
                      comp);
}

template <class Container>
Container merge(const Container& container1,
                const Container& container2) {
    Container result;
    std::merge(begin(container1), end(container1), begin(container2),
               end(container2), std::back_inserter(result));
    return result;
}

template <class Container, class Compare>
Container merge_with(const Container& container1,
                     const Container& container2, Compare comp) {
    Container result;
    std::merge(begin(container1), end(container1), begin(container2),
               end(container2), std::back_inserter(result), comp);
    return result;
}

template <class InputIterator1, class InputIterator2,
          class OutputIterator>
OutputIterator merge(InputIterator1 first1, InputIterator1 last1,
                     InputIterator2 first2, InputIterator2 last2,
                     OutputIterator output) {
    return std::merge(first1, last1, first2, last2, output);
}

template <class InputIterator1, class InputIterator2,
          class OutputIterator, class Compare>
OutputIterator merge_with(InputIterator1 first1, InputIterator1 last1,
                          InputIterator2 first2, InputIterator2 last2,
                          OutputIterator output, Compare comp) {
    return std::merge(first1, last1, first2, last2, output, comp);
}

template <class Container, class BidirectionalIterator>
void inplace_merge(Container& container,
                   BidirectionalIterator middle) {
    return std::inplace_merge(begin(container), middle,
                              end(container));
}

template <class Container, class BidirectionalIterator, class Compare>
void inplace_merge_with(Container& container,
                        BidirectionalIterator middle, Compare comp) {
    return std::inplace_merge(begin(container), middle,
                              end(container), comp);
}

template <class Container1, class Container2>
bool includes(const Container1& container1, const Container2& container2) {
    return std::includes(begin(container1), end(container1),
                         begin(container2), end(container2));
}

template <class Container1, class Container2, class Compare>
bool includes_with(const Container1& container1, const Container2& container2,
                   Compare comp) {
    return std::includes(begin(container1), end(container1),
                         begin(container2), end(container2), comp);
}

template <class Iterator1, class Iterator2>
bool includes(Iterator1 first1, Iterator1 last1, Iterator2 first2,
              Iterator2 last2) {
    return std::includes(first1, last1, first2, last2);
}

template <class Iterator1, class Iterator2, class Compare>
bool includes_with(Iterator1 first1, Iterator1 last1,
                   Iterator2 first2, Iterator2 last2, Compare comp) {
    return std::includes(first1, last1, first2, last2, comp);
}

template <class Container1, class Container2, class OutputIterator>
OutputIterator set_union(const Container1& container1,
                         const Container2& container2,
                         OutputIterator output) {
    return std::set_union(begin(container1), end(container1),
                          begin(container2), end(container2), output);
}

template <class Container1, class Container2, class OutputIterator,
          class Compare>
OutputIterator set_union_with(const Container1& container1,
                              const Container2& container2,
                              OutputIterator output, Compare comp) {
    return std::set_union(begin(container1), end(container1),
                          begin(container2), end(container2), output,
                          comp);
}

template <class Container, class OutputIterator>
Container set_union(const Container& container1,
                    const Container& container2) {
    Container result;
    std::set_union(begin(container1), end(container1),
                   begin(container2), end(container2),
                   std::back_inserter(result));
    return result;
}

template <class Container, class OutputIterator, class Compare>
Container set_union_with(const Container& container1,
                         const Container& container2, Compare comp) {
    Container result;
    std::set_union(begin(container1), end(container1),
                   begin(container2), end(container2),
                   std::back_inserter(result), comp);
    return result;
}

// #if __cplusplus >= 201103L
// template <class Container,
//           class InputIterator = typename Container::iterator,
//           class Compare>
// Container set_union(InputIterator first1, InputIterator last1,
//                     InputIterator first2, InputIterator last2)
// #else
template <class Container, class Compare>
Container set_union(typename iterator_type_of<Container>::type first1,
                    typename iterator_type_of<Container>::type last1,
                    typename iterator_type_of<Container>::type first2,
                    typename iterator_type_of<Container>::type last2)
// #endif
{
    Container result;
    std::set_union(first1, last1, first2, last2,
                   std::back_inserter(result));
    return result;
}

// #if __cplusplus >= 201103L
// template <class Container,
//           class InputIterator = typename Container::iterator,
//           class Compare>
// Container set_union_with(InputIterator first1, InputIterator last1,
//                          InputIterator first2, InputIterator last2,
//                          Compare comp)
// #else
template <class Container, class Compare>
Container set_union_with(
    typename iterator_type_of<Container>::type first1,
    typename iterator_type_of<Container>::type last1,
    typename iterator_type_of<Container>::type first2,
    typename iterator_type_of<Container>::type last2,
    Compare comp)
// #endif
{
    Container result;
    std::set_union(first1, last1, first2, last2,
                   std::back_inserter(result), comp);
    return result;
}

template <class InputIterator1, class InputIterator2,
          class OutputIterator>
OutputIterator set_union(InputIterator1 first1, InputIterator1 last1,
                         InputIterator2 first2, InputIterator2 last2,
                         OutputIterator output) {
    return std::set_union(first1, last1, first2, last2, output);
}

template <class InputIterator1, class InputIterator2,
          class OutputIterator, class Compare>
OutputIterator set_union_with(InputIterator1 first1,
                              InputIterator1 last1,
                              InputIterator2 first2,
                              InputIterator2 last2,
                              OutputIterator output, Compare comp) {
    return std::set_union(first1, last1, first2, last2, output, comp);
}

template <class Container1, class Container2, class OutputIterator>
OutputIterator set_intersection(const Container1& container1,
                                const Container2& container2,
                                OutputIterator output) {
    return std::set_intersection(begin(container1), end(container1),
                                 begin(container2), end(container2),
                                 output);
}

template <class Container1, class Container2, class OutputIterator,
          class Compare>
OutputIterator set_intersection_with(const Container1& container1,
                                     const Container2& container2,
                                     OutputIterator output,
                                     Compare comp) {
    return std::set_intersection(begin(container1), end(container1),
                                 begin(container2), end(container2),
                                 output, comp);
}

template <class Container, class OutputIterator>
Container set_intersection(const Container& container1,
                           const Container& container2) {
    Container result;
    std::set_intersection(begin(container1), end(container1),
                          begin(container2), end(container2),
                          std::back_inserter(result));
    return result;
}

template <class Container, class OutputIterator, class Compare>
Container set_intersection_with(const Container& container1,
                                const Container& container2,
                                Compare comp) {
    Container result;
    std::set_intersection(begin(container1), end(container1),
                          begin(container2), end(container2),
                          std::back_inserter(result), comp);
    return result;
}

// template <class Container,
//           class InputIterator = typename Container::iterator,
//           class Compare>
// Container set_intersection(InputIterator first1, InputIterator last1,
//                            InputIterator first2,
//                            InputIterator last2)
template <class Container>
Container set_intersection(typename iterator_type_of<Container>::type first1,
                           typename iterator_type_of<Container>::type last1,
                           typename iterator_type_of<Container>::type first2,
                           typename iterator_type_of<Container>::type last2)
{
    Container result;
    std::set_intersection(first1, last1, first2, last2,
                          std::back_inserter(result));
    return result;
}

// template <class Container,
//           class InputIterator = typename Container::iterator,
//           class Compare>
// Container set_intersection_with(InputIterator first1,
//                                 InputIterator last1,
//                                 InputIterator first2,
//                                 InputIterator last2, Compare comp)
template <class Container, class Compare>
Container set_intersection(typename iterator_type_of<Container>::type first1,
                           typename iterator_type_of<Container>::type last1,
                           typename iterator_type_of<Container>::type first2,
                           typename iterator_type_of<Container>::type last2,
                           Compare comp)
{
    Container result;
    std::set_intersection(first1, last1, first2, last2,
                          std::back_inserter(result), comp);
    return result;
}

template <class InputIterator1, class InputIterator2,
          class OutputIterator>
OutputIterator set_intersection(InputIterator1 first1,
                                InputIterator1 last1,
                                InputIterator2 first2,
                                InputIterator2 last2,
                                OutputIterator output) {
    return std::set_intersection(first1, last1, first2, last2,
                                 output);
}

template <class InputIterator1, class InputIterator2,
          class OutputIterator, class Compare>
OutputIterator set_intersection_with(InputIterator1 first1,
                                     InputIterator1 last1,
                                     InputIterator2 first2,
                                     InputIterator2 last2,
                                     OutputIterator output,
                                     Compare comp) {
    return std::set_intersection(first1, last1, first2, last2, output,
                                 comp);
}

template <class Container1, class Container2, class OutputIterator>
OutputIterator set_difference(const Container1& container1,
                              const Container2& container2,
                              OutputIterator output) {
    return std::set_difference(begin(container1), end(container1),
                               begin(container2), end(container2),
                               output);
}

template <class Container1, class Container2, class OutputIterator,
          class Compare>
OutputIterator set_difference_with(const Container1& container1,
                                   const Container2& container2,
                                   OutputIterator output,
                                   Compare comp) {
    return std::set_difference(begin(container1), end(container1),
                               begin(container2), end(container2),
                               output, comp);
}

template <class Container, class OutputIterator>
Container set_difference(const Container& container1,
                         const Container& container2) {
    Container result;
    std::set_difference(begin(container1), end(container1),
                        begin(container2), end(container2),
                        std::back_inserter(result));
    return result;
}

template <class Container, class OutputIterator, class Compare>
Container set_difference_with(const Container& container1,
                              const Container& container2,
                              Compare comp) {
    Container result;
    std::set_difference(begin(container1), end(container1),
                        begin(container2), end(container2),
                        std::back_inserter(result), comp);
    return result;
}

// template <class Container,
//           class InputIterator = typename Container::iterator,
//           class Compare>
// Container set_difference(InputIterator first1, InputIterator last1,
//                          InputIterator first2, InputIterator last2) {
template <class Container>
Container set_difference(
    typename iterator_type_of<Container>::type first1,
    typename iterator_type_of<Container>::type last1,
    typename iterator_type_of<Container>::type first2,
    typename iterator_type_of<Container>::type last2) {
    Container result;
    std::set_difference(first1, last1, first2, last2,
                        std::back_inserter(result));
    return result;
}

// template <class Container,
//           class InputIterator = typename Container::iterator,
//           class Compare>
// Container set_difference_with(InputIterator first1,
//                               InputIterator last1,
//                               InputIterator first2,
//                               InputIterator last2, Compare comp) {
template <class Container, class Compare>
Container set_difference_with(
    typename iterator_type_of<Container>::type first1,
    typename iterator_type_of<Container>::type last1,
    typename iterator_type_of<Container>::type first2,
    typename iterator_type_of<Container>::type last2,
    Compare comp) {
    Container result;
    std::set_difference(first1, last1, first2, last2,
                        std::back_inserter(result), comp);
    return result;
}

template <class InputIterator1, class InputIterator2,
          class OutputIterator>
OutputIterator set_difference(InputIterator1 first1,
                              InputIterator1 last1,
                              InputIterator2 first2,
                              InputIterator2 last2,
                              OutputIterator output) {
    return std::set_difference(first1, last1, first2, last2, output);
}

template <class InputIterator1, class InputIterator2,
          class OutputIterator, class Compare>
OutputIterator set_difference_with(InputIterator1 first1,
                                   InputIterator1 last1,
                                   InputIterator2 first2,
                                   InputIterator2 last2,
                                   OutputIterator output,
                                   Compare comp) {
    return std::set_difference(first1, last1, first2, last2, output,
                               comp);
}

template <class Container1, class Container2, class OutputIterator>
OutputIterator set_symmetric_difference(const Container1& container1,
                                        const Container2& container2,
                                        OutputIterator output) {
    return std::set_symmetric_difference(begin(container1),
                                         end(container1),
                                         begin(container2),
                                         end(container2), output);
}

template <class Container1, class Container2, class OutputIterator,
          class Compare>
OutputIterator set_symmetric_difference_with(const Container1& container1,
                                             const Container2& container2,
                                             OutputIterator output,
                                             Compare comp) {
    return std::set_symmetric_difference(begin(container1),
                                         end(container1),
                                         begin(container2),
                                         end(container2), output,
                                         comp);
}

template <class Container, class OutputIterator>
Container set_symmetric_difference(const Container& container1,
                                   const Container& container2) {
    Container result;
    std::set_symmetric_difference(begin(container1), end(container1),
                                  begin(container2), end(container2),
                                  std::back_inserter(result));
    return result;
}

template <class Container, class OutputIterator, class Compare>
Container set_symmetric_difference_with(const Container& container1,
                                        const Container& container2,
                                        Compare comp) {
    Container result;
    std::set_symmetric_difference(begin(container1), end(container1),
                                  begin(container2), end(container2),
                                  std::back_inserter(result), comp);
    return result;
}

// template <class Container,
//           class InputIterator = typename Container::iterator,
//           class Compare>
// Container set_symmetric_difference(InputIterator first1,
//                                    InputIterator last1,
//                                    InputIterator first2,
//                                    InputIterator last2) {
template <class Container>
Container set_symmetric_difference(
    typename iterator_type_of<Container>::type first1,
    typename iterator_type_of<Container>::type last1,
    typename iterator_type_of<Container>::type first2,
    typename iterator_type_of<Container>::type last2) {
    Container result;
    std::set_symmetric_difference(first1, last1, first2, last2,
                                  std::back_inserter(result));
    return result;
}

// template <class Container,
//           class InputIterator = typename Container::iterator,
//           class Compare>
// Container set_symmetric_difference_with(InputIterator first1,
//                                         InputIterator last1,
//                                         InputIterator first2,
//                                         InputIterator last2,
//                                         Compare comp) {
template <class Container, class Compare>
Container set_symmetric_difference_with(
    typename iterator_type_of<Container>::type first1,
    typename iterator_type_of<Container>::type last1,
    typename iterator_type_of<Container>::type first2,
    typename iterator_type_of<Container>::type last2,
    Compare comp) {
    Container result;
    std::set_symmetric_difference(first1, last1, first2, last2,
                                  std::back_inserter(result), comp);
    return result;
}

template <class InputIterator1, class InputIterator2,
          class OutputIterator>
OutputIterator set_symmetric_difference(InputIterator1 first1,
                                        InputIterator1 last1,
                                        InputIterator2 first2,
                                        InputIterator2 last2,
                                        OutputIterator output) {
    return std::set_symmetric_difference(first1, last1, first2, last2,
                                         output);
}

template <class InputIterator1, class InputIterator2,
          class OutputIterator, class Compare>
OutputIterator set_symmetric_difference_with(InputIterator1 first1,
                                             InputIterator1 last1,
                                             InputIterator2 first2,
                                             InputIterator2 last2,
                                             OutputIterator output,
                                             Compare comp) {
    return std::set_symmetric_difference(first1, last1, first2, last2,
                                         output, comp);
}

template <class Container, class T>
void push_heap_value(Container& container, IF_CPLUSPLUS_11(T&&, const T&) val) {
    container.push_back(forward(val));
    return std::push_heap(begin(container), end(container));
}

template <class Container, class T, class Compare>
void push_heap_value_with(Container& container, IF_CPLUSPLUS_11(T&&, const T&) val,
                          Compare comp) {
    container.push_back(forward(val));
    return std::push_heap(begin(container), end(container), comp);
}

template <class Container>
void push_heap(Container& container) {
    return std::push_heap(begin(container), end(container));
}

template <class Container, class Compare>
void push_heap_with(Container& container, Compare comp) {
    return std::push_heap(begin(container), end(container), comp);
}

template <class RandomAccessIterator>
void push_heap(RandomAccessIterator first,
               RandomAccessIterator last) {
    return std::push_heap(first, last);
}

template <class RandomAccessIterator, class Compare>
void push_heap_with(RandomAccessIterator first,
                    RandomAccessIterator last, Compare comp) {
    return std::push_heap(first, last, comp);
}

template <class Container>
void pop_heap_value(Container& container) {
    container.pop_back();
    return std::pop_heap(begin(container), end(container));
}

template <class Container, class Compare>
void pop_heap_value_with(Container& container, Compare comp) {
    container.pop_back();
    return std::pop_heap(begin(container), end(container), comp);
}

template <class Container>
void pop_heap(Container& container) {
    return std::pop_heap(begin(container), end(container));
}

template <class Container, class Compare>
void pop_heap_with(Container& container, Compare comp) {
    return std::pop_heap(begin(container), end(container), comp);
}

template <class RandomAccessIterator>
void pop_heap(RandomAccessIterator first, RandomAccessIterator last) {
    return std::pop_heap(first, last);
}

template <class RandomAccessIterator, class Compare>
void pop_heap_with(RandomAccessIterator first,
                   RandomAccessIterator last, Compare comp) {
    return std::pop_heap(first, last, comp);
}

template <class Container>
void make_heap(Container& container) {
    return std::make_heap(begin(container), end(container));
}

template <class Container, class Compare>
void make_heap_with(Container& container, Compare comp) {
    return std::make_heap(begin(container), end(container), comp);
}

template <class RandomAccessIterator>
void make_heap(RandomAccessIterator first,
               RandomAccessIterator last) {
    return std::make_heap(first, last);
}

template <class RandomAccessIterator, class Compare>
void make_heap_with(RandomAccessIterator first,
                    RandomAccessIterator last, Compare comp) {
    return std::make_heap(first, last, comp);
}

template <class Container>
void sort_heap(Container& container) {
    return std::sort_heap(begin(container), end(container));
}

template <class Container, class Compare>
void sort_heap_with(Container& container, Compare comp) {
    return std::sort_heap(begin(container), end(container), comp);
}

template <class RandomAccessIterator>
void sort_heap(RandomAccessIterator first,
               RandomAccessIterator last) {
    return std::sort_heap(first, last);
}

template <class RandomAccessIterator, class Compare>
void sort_heap_with(RandomAccessIterator first,
                    RandomAccessIterator last, Compare comp) {
    return std::sort_heap(first, last, comp);
}

#if __cplusplus >= 201103L
template <class RandomAccessIterator>
bool is_heap(RandomAccessIterator first, RandomAccessIterator last) {
    return std::is_heap(first, last);
}

template <class RandomAccessIterator, class Compare>
bool is_heap_with(RandomAccessIterator first,
                  RandomAccessIterator last, Compare comp) {
    return std::is_heap(first, last, comp);
}
#else
#if defined(__GCC__) or defined(__clang__)
template <class RandomAccessIterator>
bool is_heap(RandomAccessIterator first, RandomAccessIterator last) {
    RandomAccessIterator parent = first;
    for (RandomAccessIterator child = first + 1; child < last; ++child) {
        if (*parent < *child) {
            return false;
        } else if (((child - first) & 1) == 0) {
            ++parent;
        }
    }
    return true;
}

template <class RandomAccessIterator, class Compare>
bool is_heap_with(RandomAccessIterator first, RandomAccessIterator last, Compare comp) {
    RandomAccessIterator parent = first;
    for (RandomAccessIterator child = first + 1; child < last; ++child) {
        if (comp(*parent, *child)) {
            return false;
        } else if (((child - first) & 1) == 0) {
            ++parent;
        }
    }
    return true;
}
// TODO: implement for MSVC
#endif
#endif

template <class Container>
bool is_heap(const Container& container) {
    return is_heap(begin(container), end(container));
}

template <class Container, class Compare>
bool is_heap_with(const Container& container, Compare comp) {
    return is_heap_with(begin(container), end(container), comp);
}

#if __cplusplus >= 201103L
template <class RandomAccessIterator>
RandomAccessIterator is_heap_until(RandomAccessIterator first, RandomAccessIterator last) {
    return std::is_heap_until(first, last);
}

template <class RandomAccessIterator, class Compare>
RandomAccessIterator is_heap_until_with(RandomAccessIterator first,
                  RandomAccessIterator last, Compare comp) {
    return std::is_heap_until(first, last, comp);
}
#else
#if defined(__GCC__) or defined(__clang__)
template <class RandomAccessIterator>
RandomAccessIterator is_heap_until(RandomAccessIterator first, RandomAccessIterator last) {
    RandomAccessIterator parent = first;
    for (RandomAccessIterator child = first + 1; child < last; ++child) {
        if (*parent < *child) {
            return child;
        } else if (((child - first) & 1) == 0) {
            ++parent;
        }
    }
    return last;
}

template <class RandomAccessIterator, class Compare>
RandomAccessIterator is_heap_until_with(RandomAccessIterator first, RandomAccessIterator last, Compare comp) {
    RandomAccessIterator parent = first;
    for (RandomAccessIterator child = first + 1; child < last; ++child) {
        if (comp(*parent, *child)) {
            return child;
        } else if (((child - first) & 1) == 0) {
            ++parent;
        }
    }
    return last;
}
// TODO: implement for MSVC
#endif
#endif

template <class Container>
IF_CPLUSPLUS_11(auto, typename iterator_type_of<Container>::type)
    is_heap_until(const Container& container)
    #if __cplusplus >= 201103L
    -> decltype(std::is_heap_until(begin(container),
                                   end(container)))
    #endif
{
    return is_heap_until(begin(container), end(container));
}

template <class Container, class Compare>
IF_CPLUSPLUS_11(auto, typename iterator_type_of<Container>::type)
    is_heap_until_with(const Container& container, Compare comp)
    #if __cplusplus >= 201103L
    -> decltype(std::is_heap_until(begin(container), end(container),
                                   comp))
    #endif
{
    return is_heap_until_with(begin(container), end(container), comp);
}

using ::std::min;
using ::std::max;

#if __cplusplus >= 201103L
using ::std::minmax;
#else
template <class T>
std::pair<const T&, const T&> minmax(const T& a, const T& b) {
    return b < a ? std::make_pair(b, a) : std::make_pair(a, b);
}

template <class T, class Compare>
std::pair<const T&, const T&> minmax(const T& a, const T& b, Compare comp) {
    return comp(b, a) ? std::make_pair(b, a) : std::make_pair(a, b);
}
#endif

template <class T>
std::pair<T&, T&> minmax(T& a, T& b) {
    return b < a ? std::make_pair(b, a) : std::make_pair(a, b);
}

template <class T, class Compare>
std::pair<T&, T&> minmax(T& a, T& b, Compare comp) {
    return comp(b, a) ? std::make_pair(b, a) : std::make_pair(a, b);
}

template <class Container>
IF_CPLUSPLUS_11(auto, typename iterator_type_of<Container>::type)
    min_element(Container& container)
    #if __cplusplus >= 201103L
    -> decltype(std::min_element(begin(container), end(container)))
    #endif
{
    return std::min_element(begin(container), end(container));
}

template <class Container, class Compare>
IF_CPLUSPLUS_11(auto, typename iterator_type_of<Container>::type)
    min_element_with(Container& container, Compare comp)
    #if __cplusplus >= 201103L
    -> decltype(std::min_element(begin(container), end(container),
                                 comp))
    #endif
{
    return std::min_element(begin(container), end(container), comp);
}

template <class ForwardIterator>
ForwardIterator min_element(ForwardIterator first,
                            ForwardIterator last) {
    return std::min_element(first, last);
}

template <class ForwardIterator, class Compare>
ForwardIterator min_element_with(ForwardIterator first,
                                 ForwardIterator last, Compare comp) {
    return std::min_element(first, last, comp);
}

template <class Container>
IF_CPLUSPLUS_11(auto, typename iterator_type_of<Container>::type)
    max_element(Container& container)
    #if __cplusplus >= 201103L
    -> decltype(std::max_element(begin(container), end(container)))
    #endif
{
    return std::max_element(begin(container), end(container));
}

template <class Container, class Compare>
IF_CPLUSPLUS_11(auto, typename iterator_type_of<Container>::type)
    max_element_with(Container& container, Compare comp)
    #if __cplusplus >= 201103L
    -> decltype(std::max_element(begin(container), end(container),
                                 comp))
    #endif
{
    return std::max_element(begin(container), end(container), comp);
}

template <class ForwardIterator>
ForwardIterator max_element(ForwardIterator first,
                            ForwardIterator last) {
    return std::max_element(first, last);
}

template <class ForwardIterator, class Compare>
ForwardIterator max_element_with(ForwardIterator first,
                                 ForwardIterator last, Compare comp) {
    return std::max_element(first, last, comp);
}

#if __cplusplus >= 201103L
template <class ForwardIterator>
auto minmax_element(ForwardIterator first, ForwardIterator last)
    -> decltype(std::minmax_element(first, last)) {
    return std::minmax_element(first, last);
}

template <class ForwardIterator, class Compare>
auto minmax_element_with(ForwardIterator first, ForwardIterator last,
                         Compare comp)
    -> decltype(std::minmax_element(first, last, comp)) {
    return std::minmax_element(first, last, comp);
}
#else
template <class ForwardIterator>
std::pair<ForwardIterator, ForwardIterator> minmax_element(
    ForwardIterator first, ForwardIterator last) {
    if (first == last) {
        return std::make_pair(last, last);
    }
    ForwardIterator smallest = first;
    ForwardIterator largest = first;
    while (++first != last) {
        if (*first < *smallest) {
            smallest = first;
        }
        if (*largest < *first) {
            largest = first;
        }
    }
    return std::make_pair(smallest, largest);
}
#endif

template <class Container>
IF_CPLUSPLUS_11(auto, typename iterator_type_of<Container>::type)
    minmax_element(Container& container)
    #if __cplusplus >= 201103L
    -> decltype(std::minmax_element(begin(container),
                                    end(container)))
    #endif
{
    return minmax_element(begin(container), end(container));
}

template <class Container, class Compare>
IF_CPLUSPLUS_11(auto, typename iterator_type_of<Container>::type)
    minmax_element_with(Container& container, Compare comp)
    #if __cplusplus >= 201103L
    -> decltype(std::minmax_element(begin(container), end(container),
                                    comp))
    #endif
{
    return minmax_element_with(begin(container), end(container),
                               comp);
}

template <class Container1, class Container2>
bool lexicographical_compare(const Container1& container1,
                             const Container2& container2) {
    return std::lexicographical_compare(begin(container1),
                                        end(container1),
                                        begin(container2),
                                        end(container2));
}

template <class Container1, class Container2, class Compare>
bool lexicographical_compare(const Container1& container1,
                             const Container2& container2, Compare comp) {
    return std::lexicographical_compare(begin(container1),
                                        end(container1),
                                        begin(container2),
                                        end(container2), comp);
}

template <class InputIterator1, class InputIterator2>
bool lexicographical_compare(InputIterator1 first1,
                             InputIterator1 last1,
                             InputIterator2 first2,
                             InputIterator2 last2) {
    return std::lexicographical_compare(first1, last1, first2, last2);
}

template <class InputIterator1, class InputIterator2, class Compare>
bool lexicographical_compare(InputIterator1 first1,
                             InputIterator1 last1,
                             InputIterator1 first2,
                             InputIterator1 last2, Compare comp) {
    return std::lexicographical_compare(first1, last1, first2, last2,
                                        comp);
}

template <class Container>
bool next_permutation(const Container& container) {
    return std::next_permutation(begin(container), end(container));
}

template <class Container, class Compare>
bool next_permutation_with(const Container& container, Compare comp) {
    return std::next_permutation(begin(container), end(container),
                                 comp);
}

template <class BidirectionalIterator>
bool next_permutation(BidirectionalIterator first,
                      BidirectionalIterator last) {
    return std::next_permutation(first, last);
}

template <class BidirectionalIterator, class Compare>
bool next_permutation_with(BidirectionalIterator first,
                           BidirectionalIterator last, Compare comp) {
    return std::next_permutation(first, last, comp);
}

template <class Container>
bool prev_permutation(const Container& container) {
    return std::prev_permutation(begin(container), end(container));
}

template <class Container, class Compare>
bool prev_permutation_with(const Container& container, Compare comp) {
    return std::prev_permutation(begin(container), end(container),
                                 comp);
}

template <class BidirectionalIterator>
bool prev_permutation(BidirectionalIterator first,
                      BidirectionalIterator last) {
    return std::prev_permutation(first, last);
}

template <class BidirectionalIterator, class Compare>
bool prev_permutation_with(BidirectionalIterator first,
                           BidirectionalIterator last, Compare comp) {
    return std::prev_permutation(first, last, comp);
}
// #endif

/////////////////////////
/// MY OWN ALGORITHMS ///
/////////////////////////
template <class Container1, class Container2>
void append(Container1& container1, const Container2& container2) {
    container1.reserve(container1.size() + container2.size());
    for (typename iterator_type_of<Container1>::type it =
             begin(container2);
         it != end(container2); ++it) {
        container1.push_back(*it);
    }
}

template <class Container1, class Container2, class OutputIterator>
void append_copy(const Container1& container1, const Container2& container2,
                 OutputIterator output) {
    for (typename iterator_type_of<Container1>::type it = begin(container1); it != end(container1); ++it) {
        *output++ = *it;
    }
    for (typename iterator_type_of<Container2>::type it = begin(container2); it != end(container2); ++it) {
        *output++ = *it;
    }
}

template <class Container1, class Container2>
Container1 append_copy(const Container1& container1,
                       const Container2& container2) {
    Container1 result;
    result.reserve(container1.size() + container2.size());
    for (typename iterator_type_of<Container1>::type it = begin(container1); it != end(container1); ++it) {
        result.push_back(*it);
    }
    for (typename iterator_type_of<Container2>::type it = begin(container2); it != end(container2); ++it) {
        result.push_back(*it);
    }
    return result;
}

template <class NumType>
NumType transform_range(NumType val, NumType min_val, NumType max_val,
                        NumType min_result, NumType max_result) {
    assert(val >= min_val);
    assert(val <= max_val);
    NumType result = (val - min_val) / (max_val - min_val) * (max_result - min_result);
    assert(result >= min_result);
    assert(result <= max_result);
    return result;
}

#undef IF_CPLUSPLUS_11
}

#endif
