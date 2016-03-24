#include "catch.hpp"

#include "../src/predicate.hh"

using namespace prelude;

TEST_CASE("is_less_than") {
    BinaryPredicate<int, less<int> > pred = is_less_than(3);
    REQUIRE(pred(2));
    REQUIRE_FALSE(pred(3));
    REQUIRE_FALSE(pred(4));
}

TEST_CASE("is_greater_than") {
    BinaryPredicate<int, greater<int> > pred =
        is_greater_than(3);
    REQUIRE_FALSE(pred(2));
    REQUIRE_FALSE(pred(3));
    REQUIRE(pred(4));
}

TEST_CASE("is_equal_to") {
    BinaryPredicate<int, equal_to<int> > pred = is_equal_to(3);
    REQUIRE_FALSE(pred(2));
    REQUIRE(pred(3));
    REQUIRE_FALSE(pred(4));
}

TEST_CASE("is_less_than_or_equal_to") {
    BinaryPredicate<int, less_equal<int> > pred =
        is_less_than_or_equal_to(3);
    REQUIRE(pred(2));
    REQUIRE(pred(3));
    REQUIRE_FALSE(pred(4));
}

TEST_CASE("is_greater_than_or_equal_to") {
    BinaryPredicate<int, greater_equal<int> > pred =
        is_greater_than_or_equal_to(3);
    REQUIRE(pred(3));
    REQUIRE(pred(4));
    REQUIRE_FALSE(pred(2));
}

TEST_CASE("is_odd") {
    bool (*pred)(int) = is_odd;
    REQUIRE(pred(3));
    REQUIRE(pred(1));
    REQUIRE(pred(-1));
    REQUIRE(pred(-3));
    REQUIRE_FALSE(pred(-2));
    REQUIRE_FALSE(pred(0));
    REQUIRE_FALSE(pred(2));
    REQUIRE_FALSE(pred(4));
}

TEST_CASE("is_even") {
    bool (*pred)(int) = is_even;
    REQUIRE_FALSE(pred(3));
    REQUIRE_FALSE(pred(1));
    REQUIRE_FALSE(pred(-1));
    REQUIRE_FALSE(pred(-3));
    REQUIRE(pred(-2));
    REQUIRE(pred(0));
    REQUIRE(pred(2));
    REQUIRE(pred(4));
}

TEST_CASE("not1") {
    // greater than or equal to
    unary_negate<BinaryPredicate<int, less<int> > > pred =
        not1(is_less_than(3));
    REQUIRE_FALSE(pred(2));
    REQUIRE(pred(3));
    REQUIRE(pred(4));
}
