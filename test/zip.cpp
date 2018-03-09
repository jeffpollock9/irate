
#include <list>
#include <vector>

#include "catch/catch.hpp"

#include "irate.hpp"

using irate::zip;

TEST_CASE("zip vector, const list, different sizes", "[zip]")
{
    std::vector vec{1.0, 200.0, 3.0, 4.0, 42.0, 100.0, 42.0};
    const std::list lst{'i', 'r', 'a', 't', 'e'};

    auto vec_iter = vec.begin();
    auto lst_iter = lst.begin();

    for (auto [v, l] : zip(vec, lst))
    {
        REQUIRE(v == *vec_iter);
        REQUIRE(l == *lst_iter);

        ++vec_iter;
        ++lst_iter;
    }
}

TEST_CASE("zip two vectors, modify one", "[zip]")
{
    const std::vector vec1{1.0, 200.0, 3.0, 4.0, 42.0, 100.0, 42.0};
    std::vector<double> vec2(vec1.size());

    for (auto&& [v1, v2] : zip(vec1, vec2))
    {
        v2 = v1;
    }

    REQUIRE(vec1 == vec2);
}
