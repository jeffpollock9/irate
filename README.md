# irate

A C++17 library for iterating over C++ containers, ideas stolen shamelessly from
python.

# contents

- [install](#install)
- [functionallity](#functionallity)
    * [zip](#zip)
    * [enumerate](#enumerate)
    * [range](#range)
- [test](#test)

## install

irate is header only so you can simply copy the include folder into your own
project. TODO: write some cmake targets and document them.

## functionallity

### zip

Allows iterating over any number of containers simultaneously. Iteration will
stop upon reaching the end of the shortest container:

```c++
int main()
{
    using irate::zip;

    std::vector vec{1.0, 20.0, 3.0, 4.0, 42.0, 100.0, 42.0};
    const std::list lst{'i', 'r', 'a', 't', 'e'};

    for (auto [v, l] : zip(vec, lst))
    {
        std::cout << "[" << v << ", " << l << "]\n";
    }

    return 0;
}
```

output:

```bash
[1, i]
[20, r]
[3, a]
[4, t]
[42, e]
```

### enumerate

Iterate over a single container along with an index which may start at any value
(`enumerate(x, start)`) or from 0 by default (`enumerate(x)`):

```c++
int main()
{
    using irate::enumerate;

    const std::vector vec{42.0, 666.0, 3.14};

    for (auto [ix, val] : enumerate(vec, 10))
    {
        std::cout << "[" << ix << ", " << val << "]\n";
    }

    return 0;
}
```

output:

```bash
[10, 42]
[11, 666]
[12, 3.14]
```

### range

As in python, `range(end)`, `range(begin, end)`, and `range(begin, end, step)`
are supported. In the simplest case:

```c++
int main()
{
    using irate::range;

    for (auto ix : range(5))
    {
        std::cout << ix << "\n";
    }

    return 0;
}
```

output:

```bash
0
1
2
3
4
```

## testing

irate uses [catch](https://github.com/catchorg/Catch2) for unit testing. To
build and run the tests pass `-DIRATE_TEST=ON` to the `cmake` command then you
can build the tests with `make` and run them with `ctest` or by running the test
binaries in `build/test`.
