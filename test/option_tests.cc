#include "catch.hpp"
#include "../src/option.hh"

using namespace prelude;

class SetDestructor {
    int& to_set;

public:
    SetDestructor(int& to_set) : to_set(to_set) {}
    ~SetDestructor() { ++to_set; }
};

TEST_CASE("destructor in option") {
    int value = 0;
    SetDestructor v(value);
    {
        option<SetDestructor> op = v;
    }
    REQUIRE(value == 1);
}

TEST_CASE("destructor on copy") {
    int value = 0;
    SetDestructor v(value);
    {
        option<SetDestructor> op = v;
        REQUIRE(value == 0);
        op = none;
        REQUIRE(value == 1);
        op = v;
    }
    REQUIRE(value == 2);
}
