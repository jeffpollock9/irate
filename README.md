# irate

A C++17 library for iterating over C++ containers, ideas stolen shamelessly from
python.

# contents

- [install](#install)
- [functionallity](#functionallity)
    * [zip](#zip)
    * [enumerate](#enumerate)
    * [range](#range)
- [testing](#testing)
- [benchmark](#benchmark)

## install

irate is header only so you can simply copy the include folder into your own
project. Alternatively you can install irate somewhere via the install target
and pick up the irate config file.

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

## benchmark

A simple benchmark can be built by adding the cmake variable
`-DIRATE_BENCHMARK=ON`. It requires [google
benchmark](https://github.com/google/benchmark) and
[range-v3](https://github.com/ericniebler/range-v3) to be installed
somewhere. If they are installed in a non-standard location (i.e. not
/usr/local) then you can pass their install location to cmake via:
`-DCMAKE_PREFIX_PATH="path/to/benchmark/install;path/to/range-v3/install"`.

On my laptop the benchmark results are:

```bash
jeff@jeff-laptop:~/workspace/irate/build$ ./benchmark/zip_bench
2018-03-30 16:56:09
Running ./benchmark/zip_bench
Run on (4 X 2800 MHz CPU s)
CPU Caches:
  L1 Data 32K (x2)
  L1 Instruction 32K (x2)
  L2 Unified 256K (x2)
  L3 Unified 3072K (x1)
---------------------------------------------------------------
Benchmark                        Time           CPU Iterations
---------------------------------------------------------------
fixture/BM_irate_zip          3592 ns       3592 ns     192381
fixture/BM_range_v3_zip       2230 ns       2230 ns     311685
fixture/BM_loop               2231 ns       2231 ns     312199
```

So looks like irate is a bit behind! Remember to pass
`-DCMAKE_BUILD_TYPE=Release` when running benchmarks!
