#if __cplusplus >= 201103L

#include "catch.hpp"
#include "../src/metaprogramming.hh"
#include <iostream>

using namespace prelude;

TEST_CASE("max_sized_struct") {
    max_sized_struct<char, int>::type i;

    if (sizeof(char) > sizeof(int)) {
        bool is_char = std::is_same<decltype(i), char>::value;
        REQUIRE(is_char);
    } else {
        bool is_int = std::is_same<decltype(i), int>::value;
        REQUIRE(is_int);
    }
}

TEST_CASE("min_sized_struct") {
    min_sized_struct<char, int>::type i;

    if (sizeof(char) < sizeof(int)) {
        bool is_char = std::is_same<decltype(i), char>::value;
        REQUIRE(is_char);
    } else {
        bool is_int = std::is_same<decltype(i), int>::value;
        REQUIRE(is_int);
    }
}

TEST_CASE("static_type_if") {
    static_type_if<true, int, long>::type i;
    static_type_if<false, int, long>::type l;

    bool i_is_int = std::is_same<decltype(i), int>::value;
    bool l_is_long = std::is_same<decltype(l), long>::value;
    REQUIRE(i_is_int);
    REQUIRE(l_is_long);
}

TEST_CASE("is_one_of") {
    bool char_int_char = is_one_of<char, int, char>::value;
    REQUIRE(char_int_char);
    bool char_ = is_one_of<char>::value;
    REQUIRE_FALSE(char_);
    bool char_int_long_bool = is_one_of<char, int, long, bool>::value;
    REQUIRE_FALSE(char_int_long_bool);
    bool char_char = is_one_of<char, char>::value;
    REQUIRE(char_char);
}

TEST_CASE("count_types") {
    size_t t3 = count_types<int, char, long>::value;
    REQUIRE(t3 == 3);
    size_t t5 = count_types<int, char, long, int, long>::value;
    REQUIRE(t5 == 5);
}

TEST_CASE("index_type") {
    size_t t3 =
        index_type<int, char, long, bool, int, long, bool>::value;
    REQUIRE(t3 == 3);
    size_t t0 = index_type<int, int, long>::value;
    REQUIRE(t0 == 0);
}

TEST_CASE("first_type") {
    bool is_same = std::is_same<int, first_type<int, long>::type >::value;
    REQUIRE(is_same);
}

TEST_CASE("last_type") {
    bool is_same = std::is_same<int, last_type<long, bool, int>::type>::value;
    REQUIRE(is_same);
}

TEST_CASE("variant test") {
    Variant<int, long> var = int(5);
    REQUIRE(var.which_type() == 0);
}

#endif // c++11 required
