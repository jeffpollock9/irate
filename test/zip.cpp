
#include <iostream>
#include <list>
#include <vector>

#include "irate.hpp"

int main()
{
    using irate::zip;

    std::vector vec{1.0, 200.0, 3.0, 4.0, 42.0, 100.0, 42.0};
    const std::list lst{'i', 'r', 'a', 't', 'e'};

    for (auto[v1, v2] : zip(vec, lst))
    {
        std::cout << "[" << v1 << ", " << v2 << "]\n";
    }

    return 0;
}
