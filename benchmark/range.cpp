#include <benchmark/benchmark.h>
#include <irate/range.hpp>
#include <range/v3/view/indices.hpp>

struct fixture : benchmark::Fixture
{
    static constexpr int n = 100;
};

BENCHMARK_F(fixture, BM_irate)(benchmark::State& state)
{
    double sum = 0.0;
    for (auto _ : state)
    {
        sum = 0.0;
        for (auto i : irate::range(n))
        {
            sum += i;
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
        for (auto i : ranges::view::indices(n))
        {
            sum += i;
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
        sum = 0.0;
        for (std::size_t i = 0; i < n; ++i)
        {
            sum += i;
            benchmark::DoNotOptimize(sum);
        }
    }
    state.counters["test"] = sum;
}

BENCHMARK_MAIN();
