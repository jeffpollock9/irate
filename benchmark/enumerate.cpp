#include <algorithm>
#include <random>

#include <benchmark/benchmark.h>
#include <irate/enumerate.hpp>
#include <range/v3/view/indices.hpp>
#include <range/v3/view/zip.hpp>

struct fixture : benchmark::Fixture
{
    void SetUp(benchmark::State& /*state*/) override
    {
        std::mt19937 rng(666);

        std::normal_distribution dnorm(0.0, 1.0);

        dvec.resize(17);

        std::generate(dvec.begin(), dvec.end(), [&] { return dnorm(rng); });
    }

    std::vector<double> dvec;
};

BENCHMARK_F(fixture, BM_irate)(benchmark::State& state)
{
    double sum = 0.0;
    for (auto _ : state)
    {
        sum = 0.0;
        for (auto [i, x] : irate::enumerate(dvec))
        {
            sum += i * x;
            benchmark::DoNotOptimize(sum);
        }
    }
    state.counters["test"] = sum;
}

BENCHMARK_F(fixture, BM_range_v3)(benchmark::State& state)
{
    double sum = 0.0;
    for (auto _ : state)
    {
        sum = 0.0;
        for (auto [i, x] : ranges::view::zip(ranges::view::indices, dvec))
        {
            sum += i * x;
            benchmark::DoNotOptimize(sum);
        }
    }
    state.counters["test"] = sum;
}

BENCHMARK_F(fixture, BM_loop)(benchmark::State& state)
{
    double sum = 0.0;
    for (auto _ : state)
    {
        const std::size_t n = dvec.size();

        sum = 0.0;
        for (std::size_t i = 0; i < n; ++i)
        {
            const auto x = dvec[i];

            sum += i * x;
            benchmark::DoNotOptimize(sum);
        }
    }
    state.counters["test"] = sum;
}

BENCHMARK_MAIN();
