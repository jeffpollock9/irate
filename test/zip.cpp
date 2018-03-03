
#include <iostream>
#include <vector>

#include "irate.hpp"

int main()
{
    using irate::zip;

    std::vector vec1{1.0, 2.0, 3.0, 4.0};
    const std::vector vec2{42.0, 666.0, 3.14};

    for (auto[v1, v2] : zip(vec1, vec2))
    {
        std::cout << "[" << v1 << ", " << v2 << "]\n";
    }

    return 0;
}
