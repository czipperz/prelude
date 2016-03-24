#ifndef HEADER_GUARD_TYPE_TRAITS_H
#define HEADER_GUARD_TYPE_TRAITS_H

#include <stddef.h>
namespace prelude {
template <class T>
struct type_declaration {
    static
#if __cplusplus >= 201103L
    constexpr
#else
    const
#endif
    size_t size = sizeof(T);
    typedef T type;
    typedef T value_type;
};
}

#if __cplusplus >= 201103L

#include <type_traits>
namespace prelude {
using ::std::integral_constant;
using ::std::true_type;
using ::std::false_type;
}

#else

namespace prelude {
template <class T, T v>
struct integral_constant {
    static const T value = v;
    typedef T value_type;
    typedef integral_constant<T, v> type;
    const operator T() const { return v; }
};

typedef integral_constant<bool, true> true_type;
typedef integral_constant<bool, false> false_type;

template <class T>
struct is_array : false_type {};
template <class T>
struct is_array<T[]> : true_type {};
template <class T, size_t N>
struct is_array<T[N]> : true_type {};

template <class T>
struct is_floating_point : false_type {};
template <>
struct is_floating_point<float> : true_type {};
template <>
struct is_floating_point<double> : true_type {};
template <>
struct is_floating_point<long double> : true_type {};

template <class T>
struct is_function_impl : false_type {};
template <class Ret, class A>
struct is_function_impl<Ret(A)> : true_type {};
template <class Ret, class A, class B>
struct is_function_impl<Ret(A, B)> : true_type {};
template <class Ret, class A, class B, class C>
struct is_function_impl<Ret(A, B, C)> : true_type {};
template <class Ret, class A, class B, class C, class D>
struct is_function_impl<Ret(A, B, C, D)> : true_type {};
template <class Ret, class A, class B, class C, class D, class E>
struct is_function_impl<Ret(A, B, C, D, E)> : true_type {};
template <class Ret, class A, class B, class C, class D, class E,
          class F>
struct is_function_impl<Ret(A, B, C, D, E, F)> : true_type {};
template <class Ret, class A, class B, class C, class D, class E,
          class F, class G>
struct is_function_impl<Ret(A, B, C, D, E, F, G)> : true_type {};
template <class Ret, class A, class B, class C, class D, class E,
          class F, class G, class H>
struct is_function_impl<Ret(A, B, C, D, E, F, G, H)> : true_type {};
template <class Ret, class A, class B, class C, class D, class E,
          class F, class G, class H, class I>
struct is_function_impl<Ret(A, B, C, D, E, F, G, H, I)> : true_type {};
template <class Ret, class A, class B, class C, class D, class E,
          class F, class G, class H, class I, class J>
struct is_function_impl<Ret(A, B, C, D, E, F, G, H, I, J)> : true_type {};
template <class Ret, class A, class B, class C, class D, class E,
          class F, class G, class H, class I, class J, class K>
struct is_function_impl<Ret(A, B, C, D, E, F, G, H, I, J, K)> : true_type {
};
template <class Ret, class A, class B, class C, class D, class E,
          class F, class G, class H, class I, class J, class K,
          class L>
struct is_function_impl<Ret(A, B, C, D, E, F, G, H, I, J, K, L)>
    : true_type {};
template <class Ret, class A, class B, class C, class D, class E,
          class F, class G, class H, class I, class J, class K,
          class L, class M>
struct is_function_impl<Ret(A, B, C, D, E, F, G, H, I, J, K, L, M)>
    : true_type {};
template <class Ret, class A, class B, class C, class D, class E,
          class F, class G, class H, class I, class J, class K,
          class L, class M, class N>
struct is_function_impl<Ret(A, B, C, D, E, F, G, H, I, J, K, L, M, N)>
    : true_type {};
template <class Ret, class A, class B, class C, class D, class E,
          class F, class G, class H, class I, class J, class K,
          class L, class M, class N, class O>
struct is_function_impl<Ret(A, B, C, D, E, F, G, H, I, J, K, L, M, N, O)>
    : true_type {};
template <class Ret, class A, class B, class C, class D, class E,
          class F, class G, class H, class I, class J, class K,
          class L, class M, class N, class O, class P>
struct is_function_impl<Ret(A, B, C, D, E, F, G, H, I, J, K, L, M, N, O,
                       P)> : true_type {};
template <class Ret, class A, class B, class C, class D, class E,
          class F, class G, class H, class I, class J, class K,
          class L, class M, class N, class O, class P, class Q>
struct is_function_impl<Ret(A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P,
                       Q)> : true_type {};
template <class Ret, class A, class B, class C, class D, class E,
          class F, class G, class H, class I, class J, class K,
          class L, class M, class N, class O, class P, class Q,
          class R>
struct is_function_impl<Ret(A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P,
                       Q, R)> : true_type {};
template <class Ret, class A, class B, class C, class D, class E,
          class F, class G, class H, class I, class J, class K,
          class L, class M, class N, class O, class P, class Q,
          class R, class S>
struct is_function_impl<Ret(A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P,
                       Q, R, S)> : true_type {};
template <class Ret, class A, class B, class C, class D, class E,
          class F, class G, class H, class I, class J, class K,
          class L, class M, class N, class O, class P, class Q,
          class R, class S, class T>
struct is_function_impl<Ret(A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P,
                       Q, R, S, T)> : true_type {};
template <class Ret, class A, class B, class C, class D, class E,
          class F, class G, class H, class I, class J, class K,
          class L, class M, class N, class O, class P, class Q,
          class R, class S, class T, class U>
struct is_function_impl<Ret(A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P,
                       Q, R, S, T, U)> : true_type {};
template <class Ret, class A, class B, class C, class D, class E,
          class F, class G, class H, class I, class J, class K,
          class L, class M, class N, class O, class P, class Q,
          class R, class S, class T, class U, class V>
struct is_function_impl<Ret(A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P,
                       Q, R, S, T, U, V)> : true_type {};
template <class Ret, class A, class B, class C, class D, class E,
          class F, class G, class H, class I, class J, class K,
          class L, class M, class N, class O, class P, class Q,
          class R, class S, class T, class U, class V, class W>
struct is_function_impl<Ret(A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P,
                       Q, R, S, T, U, V, W)> : true_type {};
template <class Ret, class A, class B, class C, class D, class E,
          class F, class G, class H, class I, class J, class K,
          class L, class M, class N, class O, class P, class Q,
          class R, class S, class T, class U, class V, class W,
          class X>
struct is_function_impl<Ret(A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P,
                       Q, R, S, T, U, V, W, X)> : true_type {};
template <class Ret, class A, class B, class C, class D, class E,
          class F, class G, class H, class I, class J, class K,
          class L, class M, class N, class O, class P, class Q,
          class R, class S, class T, class U, class V, class W,
          class X, class Y>
struct is_function_impl<Ret(A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P,
                       Q, R, S, T, U, V, W, X, Y)> : true_type {};
template <class Ret, class A, class B, class C, class D, class E,
          class F, class G, class H, class I, class J, class K,
          class L, class M, class N, class O, class P, class Q,
          class R, class S, class T, class U, class V, class W,
          class X, class Y, class Z>
struct is_function_impl<Ret(A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P,
                       Q, R, S, T, U, V, W, X, Y, Z)> : true_type {};

template <class T>
struct remove_everything : type_declaration<T> {};

template <class T>
struct is_function : is_function_impl<typename remove_everything<T>::type > {};

template <class T>
struct remove_const : type_declaration<T> {};
template <class T>
struct remove_const<const T> : type_declaration<T> {};

template <class T>
struct remove_reference : type_declaration<T> {};
template <class T>
struct remove_reference<T&> : type_declaration<T> {};
}

#endif // cplusplus 11
#endif
