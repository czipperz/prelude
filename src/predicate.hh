#ifndef HEADER_GUARD_PREDICATE_H
#define HEADER_GUARD_PREDICATE_H

#include <functional>

namespace prelude {

using ::std::unary_negate;
using ::std::binary_negate;

using ::std::not1;
using ::std::not2;

template <class T, class R>
struct UnaryFunction : public ::std::unary_function<T, R> {};
template <class T>
struct UnaryPredicate : public ::std::unary_function<T, bool> {};

template <class T, class Comp1, class Comp2, class CompOverall>
class CombinatoryPredicate : UnaryPredicate<T> {
    T t;
    Comp1 comp1;
    Comp2 comp2;
    CompOverall comp_overall;

public:
    CombinatoryPredicate(T t, Comp1 comp1, Comp2 comp2, CompOverall comp_overall)
        : t(t)
        , comp1(comp1)
        , comp2(comp2)
        , comp_overall(comp_overall) {}

    bool operator()(T x) const {
        return comp_overall(comp1(x, t), comp2(x, t));
    }

    template <class CompOther>
    CombinatoryPredicate<
        T, CombinatoryPredicate<T, Comp1, Comp2, CompOverall>,
        CompOther, std::logical_and<bool> >
    operator and(CompOther comp_other) const {
        return CombinatoryPredicate<
            T, CombinatoryPredicate<T, Comp1, Comp2, CompOverall>,
            CompOther,
            std::logical_and<bool> >(t, *this, comp_other,
                                     std::logical_and<bool>());
    }

    template <class CompOther>
    CombinatoryPredicate<
        T, CombinatoryPredicate<T, Comp1, Comp2, CompOverall>,
        CompOther, std::logical_or<bool> >
    operator or(CompOther comp_other) const {
        return CombinatoryPredicate<
            T, CombinatoryPredicate<T, Comp1, Comp2, CompOverall>,
            CompOther,
            std::logical_or<bool> >(t, *this, comp_other,
                                    std::logical_or<bool>());
    }

    unary_negate<CombinatoryPredicate<T, Comp1, Comp2, CompOverall> >
    operator not() const {
        return not1(*this);
    }
};

template <class T, class Comp>
class BinaryPredicate : public UnaryPredicate<T> {
    T t;
    Comp comp;

public:
    BinaryPredicate(T t, Comp comp)
        : t(t)
        , comp(comp) {}

    bool operator()(T x) const {
        return comp(x, t);
    }

    template <class CompOther>
    CombinatoryPredicate<T, Comp, CompOther, std::logical_or<bool> >
    operator or(CompOther comp_other) const {
        return CombinatoryPredicate<
            T, Comp, CompOther,
            std::logical_or<bool> >(t, *this, comp_other,
                                    std::logical_or<bool>());
    }

    template <class CompOther>
    CombinatoryPredicate<T, Comp, CompOther, std::logical_and<bool> >
    operator and(CompOther comp_other) const {
        return CombinatoryPredicate<
            T, Comp, CompOther,
            std::logical_and<bool> >(t, *this, comp_other,
                                     std::logical_and<bool>());
    }

    unary_negate<BinaryPredicate<T, Comp> >
    operator not() const {
        return not1(*this);
    }
};

#define X(name, function) \
    template <class T> \
    inline \
    BinaryPredicate<T, std::function<T> > name(T t) { \
        return BinaryPredicate<T, std::function<T> >(t, std::function<T>()); \
    }

X(is_less_than, less)
X(is_less, less)

using ::std::less;

X(is_greater_than, greater)
X(is_greater, greater)

using ::std::greater;

X(is_equal_to, equal_to)
X(is_equal, equal_to)

using ::std::equal_to;

X(is_less_than_or_equal_to, less_equal)
X(is_less_equal, less_equal)

using ::std::less_equal;

X(is_greater_than_or_equal_to, greater_equal)
X(is_greater_equal, greater_equal)

using ::std::greater_equal;

#undef X
#undef C

template <class T>
class DivisibilityPredicate : public UnaryPredicate<T> {
    T t;
public:
    DivisibilityPredicate(T t)
        : t(t) {}
    bool operator()(T x) const {
        return x % t == 0;
    }
};

template <class T>
BinaryPredicate<T, DivisibilityPredicate<T> > is_divisible_by(T t) {
    return BinaryPredicate<T, DivisibilityPredicate<T> >(
        t, DivisibilityPredicate<T>());
}

template <class T>
T abs(T t) {
    return t < 0 ? -t : t;
}

template <class T>
struct OddPredicate : public UnaryPredicate<T> {
    bool operator()(T t) const {
        return abs(t) % 2 == 1;
    }
};

template <class T>
bool is_odd(T t) {
    return abs(t) % 2 == 1;
}

template <class T>
OddPredicate<T> is_odd() {
    return OddPredicate<T>();
}

template <class T>
struct EvenPredicate : public UnaryPredicate<T> {
    bool operator()(T t) const {
        return abs(t) % 2 == 0;
    }
};

template <class T>
bool is_even(T t) {
    return abs(t) % 2 == 0;
}

template <class T>
EvenPredicate<T> is_even() {
    return EvenPredicate<T>();
}

template <class T>
struct TruePredicate : public UnaryPredicate<T> {
    bool operator()(T t) const { return t; }
};

template <class T>
struct FalsePredicate : public UnaryPredicate<T> {
    bool operator()(T t) const { return not t; }
};

template <class T>
TruePredicate<T> is_true() {
    return TruePredicate<T>();
}

template <class T>
bool is_true(T t) {
    return t;
}

template <class T>
FalsePredicate<T> is_false() {
    return FalsePredicate<T>();
}

template <class T>
bool is_false(T t) {
    return not t;
}

}

#endif
