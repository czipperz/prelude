#ifndef HEADER_GUARD_RESULT_H
#define HEADER_GUARD_RESULT_H

#include <utility>

namespace prelude {

template <class T, class E>
class result;

template <class E, class T>
result<T, E> ok(const T& t) {
    return result<T, E>(t);
}

template <class T, class E>
result<T, E> err(const E& e) {
    return result<T, E>(e);
}

template <class T, class E>
class result {
    char storage[sizeof(T) > sizeof(E) ? sizeof(T) : sizeof(E)];
    bool holds;

    void destroy() {
        if (holds) {
            as_ok()->~T();
        } else {
            as_err()->~E();
        }
    }

public:
    result(const T& t)
        : holds(true) {
        new (storage) T(t);
    }
    result(const E& e)
        : holds(false) {
        new (storage) E(e);
    }
    ~result() { destroy(); }

    result& operator=(const T& t) {
        destroy();
        holds = true;
        new (storage) T(t);
    }
    #if __cplusplus >= 201103L
    result& operator=(T&& t) {
        destroy();
        holds = true;
        new (storage) T(std::move(t));
    }
    #endif

    result& operator=(const E& e) {
        destroy();
        holds = false;
        new (storage) E(e);
    }
    #if __cplusplus >= 201103L
    result& operator=(E&& e) {
        destroy();
        holds = false;
        new (storage) E(std::move(e));
    }
    #endif

    T* as_ok() { return reinterpret_cast<T>(storage); }
    E* as_err() { return reinterpret_cast<E>(storage); }
};
}

#endif
