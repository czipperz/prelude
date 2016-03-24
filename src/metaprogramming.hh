#ifndef HEADER_GUARD_METAPROGRAMMING_H
#define HEADER_GUARD_METAPROGRAMMING_H

#include "type_traits.hh"
#include <stddef.h>

namespace prelude {

template <class T>
struct iterator_type_of;

template <class T>
struct iterator_type_of<T*> : type_declaration<T*> {};

template <class T>
struct iterator_type_of<const T*> : type_declaration<const T*> {};

template <class T>
struct iterator_type_of : type_declaration<typename T::iterator> {};

template <class T>
struct iterator_type_of<const T>
    : type_declaration<typename T::const_iterator> {};

template <bool cond, class True, class False>
struct static_type_if;

template <class True, class False>
struct static_type_if<true, True, False> : type_declaration<True> {};

template <class True, class False>
struct static_type_if<false, True, False> : type_declaration<False> {
};

template <bool cond, class Type>
struct static_if {};
template <class Type>
struct static_if<true, Type> : type_declaration<Type> {};

template <class T>
struct return_type_0 {};
template <class Ret>
struct return_type_0<Ret()> : type_declaration<Ret> {};

template <class T>
struct return_type_1 {};
template <class A, class Ret>
struct return_type_1<Ret(A)> : type_declaration<Ret> {};

template <class T>
struct return_type_2 {};
template <class A, class B, class Ret>
struct return_type_2<Ret(A, B)> : type_declaration<Ret> {};

#if __cplusplus >= 201103L
template <class A, class... B>
struct max_sized_struct;

template <class A, class... B>
struct max_sized_struct
    : static_type_if<(sizeof(A) >= max_sized_struct<B...>::size), A,
                     typename max_sized_struct<B...>::type> {};

template <class A>
struct max_sized_struct<A> : type_declaration<A> {};

template <class A, class... B>
struct min_sized_struct;

template <class A, class... B>
struct min_sized_struct
    : static_type_if<(sizeof(A) <= min_sized_struct<B...>::size), A,
                     typename min_sized_struct<B...>::type> {};

template <class A>
struct min_sized_struct<A> : type_declaration<A> {};

template <class A, class... B>
struct first_type : type_declaration<A> {};

template <class A, class... B>
struct last_type;

template <class A>
struct last_type<A> : type_declaration<A> {};

template <class A, class... B>
struct last_type : last_type<B...> {};

template <size_t N, class A, class... B>
struct nth_type;

template <class A, class... B>
struct nth_type<0, A, B...> : type_declaration<A> {};

template <size_t N, class A, class... B>
struct nth_type : nth_type<N - 1, B...> {};

template <size_t N, class... Types>
struct count_types_impl;

template <size_t N>
struct count_types_impl<N> : std::integral_constant<size_t, N> {};

template <size_t N, class T, class... Types>
struct count_types_impl<N, T, Types...> : count_types_impl<N + 1, Types...> {};

template <class A, class... B>
using count_types = count_types_impl<0, A, B...>;

template <size_t N, class A, class B, class... Bs>
struct index_type_impl;

template <size_t N, class A, class... Bs>
struct index_type_impl<N, A, A, Bs...> : std::integral_constant<size_t, N> {};

template <size_t N, class A, class B, class... Bs>
struct index_type_impl : index_type_impl<N + 1, A, Bs...> {};

template <class A, class B, class... Bs>
using index_type = index_type_impl<0, A, B, Bs...>;

template <class A, class... ListWithMaybeA>
struct is_one_of;

template <class A>
struct is_one_of<A> : std::false_type {};

template <class A, class... ListWithMaybeA>
struct is_one_of<A, A, ListWithMaybeA...> : std::true_type {};

template <class A, class B, class... ListWithMaybeA>
struct is_one_of<A, B, ListWithMaybeA...> : is_one_of<A, ListWithMaybeA...> {};

template <class Type1, class... Types>
class Variant {
    char storage[max_sized_struct<Type1, Types...>::size];
    size_t which;

public:
    template <class Type>
    Variant(Type init)
        : which(index_type<Type, Type1, Types...>::value) {
        new (storage) Type(init);
    }

    ~Variant() {
        auto w = which;
    }

    size_t which_type() const { return which; }

    template <class Type>
    typename static_if<is_one_of<Type, Type1, Types...>::value,
                       Type>::type
    get_as() {
        return *static_cast<Type*>(storage);
    }

    template <size_t N>
    typename nth_type<N, Type1, Types...>::type
    get_n() {
        return *static_cast<
            typename nth_type<N, Type1, Types...>::type>(storage);
    }
};
#endif

}

#endif
