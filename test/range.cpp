
#include "catch/catch.hpp"

#include "irate.hpp"

using irate::range;

TEST_CASE("range 1 arg", "[range]")
{
    int step = 0;

    for (auto ix : range(10))
    {
        REQUIRE(ix == step);
        ++step;
    }

    REQUIRE(step == 10);
}

TEST_CASE("range 2 arg", "[range]")
{
    int step = -4;

    for (auto ix : range(-4, 7))
    {
        REQUIRE(ix == step);
        ++step;
    }

    REQUIRE(step == 7);
}

TEST_CASE("range 3 arg", "[range]")
{
    int step = -4;

    for (auto ix : range(-4, 7, 2))
    {
        REQUIRE(ix == step);
        step += 2;
    }

    REQUIRE(step == 8);
}
