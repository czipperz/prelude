#ifndef HEADER_GUARD_OPTION_H
#define HEADER_GUARD_OPTION_H

#include <exception>
#include <utility>
#include "metaprogramming.hh"
#include "result.hh"

namespace prelude {

template <class T>
class option;

#if __cplusplus >= 201103L
struct none_t {
    constexpr none_t() {}
};
constexpr none_t none;
#else
struct none_t {
    none_t() {}
};
const none_t none;
#endif

template <class T>
option<T> some(T t) {
    return option<T>(t);
}

class option_is_none_exception : public std::exception {
    const char* message;

public:
    option_is_none_exception()
        : message("Tried to dereference the option when there was no "
                  "held value.") {}
    option_is_none_exception(const char* message)
        : message(message) {}

    const char* what() const throw() { return message; }
};

template <class T>
class option {
    char storage[sizeof(T)];
    bool holds;

    void destroy() {
        if (holds) {
            as_ptr()->~T();
        }
    }

public:
    option()
        : holds(false) {}
    option(const T& t)
        : holds(true) {
        new (storage) T(t);
    }
#if __cplusplus >= 201103L
    option(T&& t)
        : holds(true) {
        new (storage) T(std::move(t));
    }
#endif
    option(none_t)
        : holds(false) {}
    ~option() { destroy(); }

    option& operator=(none_t) {
        destroy();
        holds = false;
        return *this;
    }
#if __cplusplus >= 201103L
    option& operator=(T&& t) {
        destroy();
        holds = true;
        new (storage) T(std::move(t));
        return *this;
    }
#endif
    option& operator=(const T& t) {
        destroy();
        holds = true;
        new (storage) T(t);
        return *this;
    }

    bool is_some() { return holds; }
    bool is_none() { return not holds; }

    T operator*() {
        if (holds) {
            return *as_ptr();
        } else {
            throw option_is_none_exception();
        }
    }

    T unwrap() { return **this; }

    T expect(const char* msg) {
        if (holds) {
            return *as_ptr();
        } else {
            throw option_is_none_exception(msg);
        }
    }

    T unwrap_or(T t) {
        if (holds) {
            return *this->as_ptr();
        } else {
            return t;
        }
    }

    template <class F>
    T unwrap_or_else(F fun) {
        if (holds) {
            return *as_ptr();
        } else {
            return fun();
        }
    }

    T* as_ptr() { return reinterpret_cast<T*>(storage); }

    template <class F>
#if __cplusplus >= 201103L
    auto map(F fun) -> decltype(some(fun(*as_ptr())))
#else
    option<typename return_type_1<F>::type> map(F fun)
#endif
    {
        if (holds) {
            return some(fun(*as_ptr()));
        } else {
            return none;
        }
    }

    template <class U, class F>
    U map_or(U def, F fun) {
        if (holds) {
            return fun(*as_ptr());
        } else {
            return def;
        }
    }

    template <class D, class F>
#if __cplusplus >= 201103L
    auto map_or_else(D def_fun, F fun) -> decltype(fun(*as_ptr()))
#else
    option<typename return_type_1<F>::type> map_or_else(D def_fun,
                                                        F fun)
#endif
    {
        if (holds) {
            return fun(*as_ptr());
        } else {
            return def_fun();
        }
    }

    template <class E>
    result<T, E> ok_or(E error) {
        if (holds) {
            return ok(*as_ptr());
        } else {
            return err(error);
        }
    }
};
}

#endif
