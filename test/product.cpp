#include <irate/product.hpp>

#include <catch/catch.hpp>

#include <array>
#include <vector>

using irate::product;

TEST_CASE("product array, const vector, different sizes", "[product]")
{
    std::array arr{1.1, 2.2, 3.3};
    const std::vector vec{10.0, 19.0, 42.0};

    double prod_ans = 0.0;
    for (auto [a, v] : product(arr, vec))
    {
        prod_ans += a * v;
    }

    double loop_ans = 0.0;
    for (auto a : arr)
    {
        for (auto v : vec)
        {
            loop_ans += a * v;
        }
    }

    REQUIRE(prod_ans == loop_ans);
}
