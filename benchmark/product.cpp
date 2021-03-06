#include <algorithm>
#include <random>

#include <benchmark/benchmark.h>
#include <irate/product.hpp>
#include <range/v3/view/cartesian_product.hpp>

struct fixture : benchmark::Fixture
{
    void SetUp(benchmark::State& /*state*/) override
    {
        std::mt19937 rng(666);

        std::normal_distribution dnorm(0.0, 1.0);
        std::normal_distribution fnorm(0.0f, 1.0f);

        dvec.resize(10);
        fvec.resize(42);

        std::generate(dvec.begin(), dvec.end(), [&] { return dnorm(rng); });
        std::generate(fvec.begin(), fvec.end(), [&] { return fnorm(rng); });
    }

    std::vector<double> dvec;
    std::vector<float> fvec;
};

BENCHMARK_F(fixture, BM_irate)(benchmark::State& state)
{
    double sum = 0.0;
    for (auto _ : state)
    {
        sum = 0.0;
        for (auto [x, y] : irate::product(dvec, fvec))
        {
            sum += x + y;
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
        for (auto [x, y] : ranges::view::cartesian_product(dvec, fvec))
        {
            sum += x + y;
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
        for (auto x : dvec)
        {
            for (auto y : fvec)
            {
                sum += x + y;
                benchmark::DoNotOptimize(sum);
            }
        }
    }
    state.counters["test"] = sum;
}

BENCHMARK_MAIN();
