#include <vector>
#include "catch.hpp"

#include "../src/algorithm.hh"
#include "../src/predicate.hh"

using namespace prelude;

#if __cplusplus >= 201103L

TEST_CASE("all_of") {
    std::vector<int> vec;

    SECTION("3, 3") {
        vec.push_back(3);
        vec.push_back(3);
        REQUIRE(all_of(vec, is_equal_to(3)));
        REQUIRE_FALSE(all_of(vec, is_equal_to(4)));
    }

    SECTION("3, 4") {
        vec.push_back(3);
        vec.push_back(4);
        REQUIRE(all_of(vec, is_less_than(5)));
        REQUIRE_FALSE(all_of(vec, is_equal_to(3)));
        REQUIRE_FALSE(all_of(vec, is_equal_to(4)));
    }

    SECTION("4, 4") {
        vec.push_back(4);
        vec.push_back(4);
        REQUIRE(all_of(vec, is_equal_to(4)));
        REQUIRE(all_of(vec, is_greater_than(3)));
        REQUIRE_FALSE(all_of(vec, is_less_than_or_equal_to(3)));
    }
}

TEST_CASE("none_of") {
    std::vector<int> vec;
    vec.push_back(3);
    vec.push_back(5);
    REQUIRE(none_of(vec, is_equal_to(4)));
    REQUIRE_FALSE(none_of(vec, is_equal_to(5)));
}

#include <iostream>
TEST_CASE("swap_ranges") {
    std::vector<int> vec1;
    vec1.push_back(1);
    vec1.push_back(2);
    vec1.push_back(3);

    std::vector<int> vec2;
    vec2.push_back(4);
    vec2.push_back(5);
    vec2.push_back(6);

    // all three should be equivalent
    SECTION("") { swap_ranges(vec1, vec2); }
    SECTION("") {
        swap_ranges(std::begin(vec1), std::end(vec1),
                    std::begin(vec2));
    }
    SECTION("") { swap_ranges_i(vec1, std::begin(vec2)); }

    REQUIRE(vec1[0] == 4);
    REQUIRE(vec1[1] == 5);
    REQUIRE(vec1[2] == 6);

    REQUIRE(vec2[0] == 1);
    REQUIRE(vec2[1] == 2);
    REQUIRE(vec2[2] == 3);
}

TEST_CASE("replace") {
    std::vector<int> vec;
    vec.push_back(3);
    vec.push_back(4);
    vec.push_back(5);

    replace(vec, 3, 6);
    REQUIRE(vec[0] == 6);
    REQUIRE(vec[1] == 4);
    REQUIRE(vec[2] == 5);
}

TEST_CASE("append") {
    std::vector<int> vec1;
    vec1.push_back(1);
    vec1.push_back(2);
    vec1.push_back(3);

    std::vector<int> vec2;
    vec2.push_back(4);
    vec2.push_back(5);
    vec2.push_back(6);

    append(vec1, vec2);
    REQUIRE(vec1.size() == 6);
    REQUIRE(vec1[0] == 1);
    REQUIRE(vec1[1] == 2);
    REQUIRE(vec1[2] == 3);
    REQUIRE(vec1[3] == 4);
    REQUIRE(vec1[4] == 5);
    REQUIRE(vec1[5] == 6);

    REQUIRE(vec2.size() == 3);
    REQUIRE(vec2[0] == 4);
    REQUIRE(vec2[1] == 5);
    REQUIRE(vec2[2] == 6);
}

TEST_CASE("append_copy") {
    std::vector<int> vec1;
    vec1.push_back(1);
    vec1.push_back(2);
    vec1.push_back(3);

    std::vector<int> vec2;
    vec2.push_back(4);
    vec2.push_back(5);
    vec2.push_back(6);

    std::vector<int> vec = append_copy(vec1, vec2);
    REQUIRE(vec.size() == 6);
    REQUIRE(vec[0] == 1);
    REQUIRE(vec[1] == 2);
    REQUIRE(vec[2] == 3);
    REQUIRE(vec[3] == 4);
    REQUIRE(vec[4] == 5);
    REQUIRE(vec[5] == 6);
}

TEST_CASE("remove_copy") {
    std::vector<int> vec;
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);

    std::vector<int> copy = remove_copy(vec, 2);
    REQUIRE(copy.size() == 2);
    REQUIRE(copy[0] == 1);
    REQUIRE(copy[1] == 3);

    REQUIRE(vec.size() == 3);
    REQUIRE(vec[0] == 1);
    REQUIRE(vec[1] == 2);
    REQUIRE(vec[2] == 3);
}

TEST_CASE("remove_copy_if") {
    std::vector<int> vec;
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);

    std::vector<int> copy = remove_copy_if(vec, is_less_than(3));
    REQUIRE(copy.size() == 1);
    REQUIRE(copy[0] == 3);

    REQUIRE(vec.size() == 3);
    REQUIRE(vec[0] == 1);
    REQUIRE(vec[1] == 2);
    REQUIRE(vec[2] == 3);
}

TEST_CASE("unique_copy") {
    std::vector<int> vec;
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);

    std::vector<int> copy = unique_copy(vec);
    REQUIRE(vec.size() == 3);
    REQUIRE(vec[0] == 1);
    REQUIRE(vec[1] == 2);
    REQUIRE(vec[2] == 3);

    REQUIRE(copy == vec);
}

TEST_CASE("unique_copy 2") {
    std::vector<int> vec;
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);
    vec.push_back(3);

    std::vector<int> copy = unique_copy(vec);
    REQUIRE(vec.size() == 4);
    REQUIRE(vec[0] == 1);
    REQUIRE(vec[1] == 2);
    REQUIRE(vec[2] == 3);
    REQUIRE(vec[3] == 3);

    REQUIRE(copy != vec);
    REQUIRE(copy.size() == 3);
    REQUIRE(copy[0] == 1);
    REQUIRE(copy[1] == 2);
    REQUIRE(copy[2] == 3);
}

#endif
