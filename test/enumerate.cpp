
#include <iostream>
#include <vector>

#include "catch/catch.hpp"

#include "irate.hpp"

TEST_CASE("enumerate const vector", "[enumerate]")
{
    using irate::enumerate;

    const std::vector vec{42.0, 666.0, 3.14};

    int step = 0;

    for (auto[ix, val] : enumerate(vec))
    {
        REQUIRE(ix == step);
        REQUIRE(val == vec[step]);
        ++step;
    }

    REQUIRE(step == 3);
}
