
#include <list>
#include <vector>

#include "catch/catch.hpp"

#include "irate.hpp"

TEST_CASE("zip vector, const list, different sizes", "[zip]")
{
    using irate::zip;

    std::vector vec{1.0, 200.0, 3.0, 4.0, 42.0, 100.0, 42.0};
    const std::list lst{'i', 'r', 'a', 't', 'e'};

    auto vec_iter = vec.begin();
    auto lst_iter = lst.begin();

    for (const auto & [ v, l ] : zip(vec, lst))
    {
        REQUIRE(v == *vec_iter);
        REQUIRE(l == *lst_iter);

        ++vec_iter;
        ++lst_iter;
    }
}
