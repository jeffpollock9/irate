#include <algorithm>
#include <numeric>

#include <benchmark/benchmark.h>
#include <range/v3/view/zip.hpp>

#include "irate.hpp"

struct fixture : benchmark::Fixture
{
    virtual void SetUp(benchmark::State& st) override
    {
        v1.resize(700);
        v2.resize(800);

        std::iota(v1.begin(), v1.end(), -777.0);
        std::iota(v2.begin(), v2.end(), 42);
    }

    std::vector<double> v1;
    std::vector<int> v2;
};

BENCHMARK_F(fixture, BM_irate_zip)(benchmark::State& state)
{
    for (auto _ : state)
    {
        double z = 0.0;

        for (auto [x, y] : irate::zip(v1, v2))
        {
            benchmark::DoNotOptimize(z += x + y);
        }
    }
}

BENCHMARK_F(fixture, BM_range_v3_zip)(benchmark::State& state)
{
    for (auto _ : state)
    {
        double z = 0.0;

        for (auto [x, y] : ranges::view::zip(v1, v2))
        {
            benchmark::DoNotOptimize(z += x + y);
        }
    }
}

BENCHMARK_F(fixture, BM_loop)(benchmark::State& state)
{
    for (auto _ : state)
    {
        std::size_t n = std::min(v1.size(), v2.size());

        double z = 0.0;

        for (std::size_t i = 0; i < n; ++i)
        {
            auto x = v1[i];
            auto y = v2[i];

            benchmark::DoNotOptimize(z += x + y);
        }
    }
}

BENCHMARK_MAIN();
