#include "catch.hpp"
#include "../src/iterator.hh"

using namespace prelude;

TEST_CASE("Iterator") {
    std::vector<char> vec;
    vec.push_back('a');
    vec.push_back('b');
    vec.push_back('c');
    vec.push_back('d');
    VectorIterator<char> vit = iterator(vec);
    Iterator<char>* it = &vit;
    for (char* c = it->get(); c; c = (++*it).get()) {
        ++*c;
    }
    REQUIRE(vec[0] == 'b');
    REQUIRE(vec[1] == 'c');
    REQUIRE(vec[2] == 'd');
    REQUIRE(vec[3] == 'e');
    // auto x = it->count();
}

TEST_CASE("begin end") {
    int array[] = {1,2,3,4,5};
    int* b = begin(array);
    int* e = end(array);
    REQUIRE(b == array);
    REQUIRE(e == array + 5);
}

TEST_CASE("const begin end") {
    const int array[] = {1,2,3,4,5};
    const int* b = begin(array);
    const int* e = end(array);
    REQUIRE(b == array);
    REQUIRE(e == array + 5);
}

TEST_CASE("const begin end for strings") {
    const char* str = "Hello world!";
    const char* first = begin(str);
    const char* last = end(str);
    REQUIRE(str == first);
    REQUIRE(str + 12 == last);
}

TEST_CASE("begin end for array of strings") {
    const char* arr[] = {"Hello", "world", "how", "you", "doing?", NULL};
    const char** ptr = arr;
    REQUIRE(begin(ptr) == ptr);
    REQUIRE(end_null(ptr) - ptr == 5);
    REQUIRE(end_null(ptr) == ptr + 5);
}
