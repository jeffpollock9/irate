
#include <iostream>
#include <vector>

#include "irate.hpp"

int main()
{
    using irate::enumerate;

    const std::vector vec{42.0, 666.0, 3.14};

    for (auto[ix, val] : enumerate(vec, 10))
    {
        std::cout << "[" << ix << ", " << val << "]\n";
    }

    return 0;
}
