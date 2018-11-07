#include <irate/enumerate.hpp>

#include <catch/catch.hpp>

#include <array>
#include <list>
#include <vector>

using irate::enumerate;

TEST_CASE("enumerate const vector", "[enumerate]")
{
    const std::vector vec{42.0, 666.0, 3.14};
    int step = 0;

    for (auto [ix, val] : enumerate(vec))
    {
        REQUIRE(ix == step);
        REQUIRE(val == vec[step++]);
    }

    REQUIRE(step == 3);
}

TEST_CASE("enumerate non const array modifiable", "[enumerate]")
{
    std::array arr{42.0, 666.0, 3.14, 0.0};
    int step = 0;

    for (auto [ix, val] : enumerate(arr))
    {
        REQUIRE(ix == step);
        REQUIRE(val == arr[step++]);
        val = 0.0;
    }

    REQUIRE(step == 4);

    for (const auto [_, val] : enumerate(arr))
    {
        REQUIRE(val == 0.0);
    }
}

TEST_CASE("enumerate with non-zero index", "[enumerate]")
{
    std::list lst{1, 2, 3, 4};
    int step = -42;

    using my_enumerate = enumerate<decltype(lst), decltype(step)>;

    for (auto [ix, val] : my_enumerate(lst, step))
    {
        REQUIRE(ix == step++);
    }

    REQUIRE(step == -38);
}
