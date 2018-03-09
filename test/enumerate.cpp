
#include <array>
#include <vector>

#include "catch/catch.hpp"

#include "irate.hpp"

using irate::enumerate;

TEST_CASE("enumerate const vector", "[enumerate]")
{
    const std::vector vec{42.0, 666.0, 3.14};

    int step = 0;

    for (auto [ix, val] : enumerate(vec))
    {
        REQUIRE(ix == step);
        REQUIRE(val == vec[step]);
        ++step;
    }

    REQUIRE(step == 3);
}

TEST_CASE("enumerate non const array modifiable", "[enumerate]")
{
    std::array<double, 4> arr{{42.0, 666.0, 3.14, 0.0}};

    int step = 0;

    for (auto && [ix, val] : enumerate(arr))
    {
        REQUIRE(ix == step);
        REQUIRE(val == arr[step]);
        ++step;
        val = 0.0;
    }

    REQUIRE(step == 4);

    for (const auto [_, val] : enumerate(arr))
    {
        REQUIRE(val == 0.0);
    }
}
