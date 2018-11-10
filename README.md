
# Table of Contents

1.  [install](#orgf366182)
2.  [functionallity](#org9528e23)
    1.  [zip](#orgb4667dc)
    2.  [enumerate](#org0b49ff3)
    3.  [range](#orgdb32004)
    4.  [product](#orgfaee27f)
3.  [testing](#orgc51fce6)
4.  [benchmark](#orgea0d995)



<a id="orgf366182"></a>

# install

irate is header only so you can simply copy the include folder into your own
project. Alternatively you can install irate somewhere via the install target
and pick up the irate cmake config file which exports the cmake target
`irate::irate`.


<a id="org9528e23"></a>

# functionallity


<a id="orgb4667dc"></a>

## zip

Allows iterating over any number of containers simultaneously. Iteration will
stop upon reaching the end of the shortest container:

    #include <irate/zip.hpp>
    
    #include <iostream>
    #include <list>
    #include <vector>
    
    int main()
    {
        std::vector vec{1.0, 20.0, 3.0, 4.0, 42.0, 100.0, 42.0};
        const std::list lst{'i', 'r', 'a', 't', 'e'};
    
        for (auto [v, l] : irate::zip(vec, lst))
        {
            std::cout << "[" << v << ", " << l << "]\n";
        }
    
        return 0;
    }

<table border="2" cellspacing="0" cellpadding="6" rules="groups" frame="hsides">


<colgroup>
<col  class="org-left" />

<col  class="org-left" />
</colgroup>
<tbody>
<tr>
<td class="org-left">[1</td>
<td class="org-left">i]</td>
</tr>


<tr>
<td class="org-left">[20</td>
<td class="org-left">r]</td>
</tr>


<tr>
<td class="org-left">[3</td>
<td class="org-left">a]</td>
</tr>


<tr>
<td class="org-left">[4</td>
<td class="org-left">t]</td>
</tr>


<tr>
<td class="org-left">[42</td>
<td class="org-left">e]</td>
</tr>
</tbody>
</table>


<a id="org0b49ff3"></a>

## enumerate

Iterate over a single container along with an index which may start at any value
(`enumerate(x, start)`) or from 0 by default (`enumerate(x)`):

    #include <irate/enumerate.hpp>
    
    #include <iostream>
    #include <vector>
    
    int main()
    {
        const std::vector vec{42.0, 666.0, 3.14};
    
        for (auto [ix, val] : irate::enumerate(vec, 10))
        {
            std::cout << "[" << ix << ", " << val << "]\n";
        }
    
        return 0;
    }

<table border="2" cellspacing="0" cellpadding="6" rules="groups" frame="hsides">


<colgroup>
<col  class="org-left" />

<col  class="org-left" />
</colgroup>
<tbody>
<tr>
<td class="org-left">[10</td>
<td class="org-left">42]</td>
</tr>


<tr>
<td class="org-left">[11</td>
<td class="org-left">666]</td>
</tr>


<tr>
<td class="org-left">[12</td>
<td class="org-left">3.14]</td>
</tr>
</tbody>
</table>


<a id="orgdb32004"></a>

## range

As in python, `range(end)`, `range(begin, end)`, and `range(begin, end, step)` are
supported. In the simplest case:

    #include <irate/range.hpp>
    
    #include <iostream>
    
    int main()
    {
        for (auto ix : irate::range(5))
        {
            std::cout << ix << "\n";
        }
        return 0;
    }

<table border="2" cellspacing="0" cellpadding="6" rules="groups" frame="hsides">


<colgroup>
<col  class="org-right" />
</colgroup>
<tbody>
<tr>
<td class="org-right">0</td>
</tr>


<tr>
<td class="org-right">1</td>
</tr>


<tr>
<td class="org-right">2</td>
</tr>


<tr>
<td class="org-right">3</td>
</tr>


<tr>
<td class="org-right">4</td>
</tr>
</tbody>
</table>


<a id="orgfaee27f"></a>

## product

Cartesian product of iterables:

    #include <irate/product.hpp>
    
    #include <iostream>
    #include <list>
    #include <vector>
    
    int main()
    {
        const std::vector vec{-10.0, 10.0, 100.0};
        const std::list lst{"foo", "bar"};
    
        for (auto [v, l] : irate::product(vec, lst))
        {
            std::cout << "[" << v << ", " << l << "]\n";
        }
    
        return 0;
    }

<table border="2" cellspacing="0" cellpadding="6" rules="groups" frame="hsides">


<colgroup>
<col  class="org-left" />

<col  class="org-left" />
</colgroup>
<tbody>
<tr>
<td class="org-left">[-10</td>
<td class="org-left">foo]</td>
</tr>


<tr>
<td class="org-left">[-10</td>
<td class="org-left">bar]</td>
</tr>


<tr>
<td class="org-left">[10</td>
<td class="org-left">foo]</td>
</tr>


<tr>
<td class="org-left">[10</td>
<td class="org-left">bar]</td>
</tr>


<tr>
<td class="org-left">[100</td>
<td class="org-left">foo]</td>
</tr>


<tr>
<td class="org-left">[100</td>
<td class="org-left">bar]</td>
</tr>
</tbody>
</table>


<a id="orgc51fce6"></a>

# testing

irate uses [catch2](https://github.com/catchorg/Catch2) for unit testing. To build and run the tests pass
`-DIRATE_TEST=ON` to the `cmake` command then you can build the tests with `make` and
run them with \`ctest\` or by running the test binaries in `build/test`.


<a id="orgea0d995"></a>

# benchmark

A simple benchmark can be built by adding the cmake variable
`-DIRATE_BENCHMARK=ON`. It requires [google benchmark](https://github.com/google/benchmark) and [range-v3](https://github.com/ericniebler/range-v3) to be installed
somewhere. If they are installed in a non-standard location (i.e. not
`/usr/local`) then you can pass their install location to cmake via:
`-DCMAKE_PREFIX_PATH="path/to/benchmark/install;path/to/range-v3/install"`.

On my laptop configuring with `-DCMAKE_BUILD_TYPE=Release
-DCMAKE_CXX_FLAGS="-march=native"`, the benchmark results are:

    ~/workspace/irate/release/benchmark/zip_benchmark --benchmark_color=false

    -------------------------------------------------------------------------------
    Benchmark                        Time           CPU Iterations UserCounters...
    -------------------------------------------------------------------------------
    fixture/BM_irate_zip            51 ns         51 ns   13492752 test=5.67854
    fixture/BM_range_v3_zip         56 ns         56 ns   12578357 test=5.67854
    fixture/BM_loop                 49 ns         49 ns   14348753 test=5.67854

    ~/workspace/irate/release/benchmark/product_benchmark --benchmark_color=false

    --------------------------------------------------------------------------------
    Benchmark                         Time           CPU Iterations UserCounters...
    --------------------------------------------------------------------------------
    fixture/BM_irate_product       1744 ns       1744 ns     400430 test=-251.067
    fixture/BM_loop                1766 ns       1766 ns     396570 test=-251.067

