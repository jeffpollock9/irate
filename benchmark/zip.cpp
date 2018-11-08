#include <algorithm>
#include <random>

#include <benchmark/benchmark.h>
#include <irate/zip.hpp>
#include <range/v3/view/zip.hpp>

struct fixture : benchmark::Fixture
{
    virtual void SetUp(benchmark::State& state) override
    {
        std::mt19937 rng(666);

        std::normal_distribution dnorm(0.0, 1.0);
        std::uniform_int_distribution iunif(-10, 10);
        std::normal_distribution fnorm(0.0f, 1.0f);

        dvec.resize(17);
        ivec.resize(42);
        fvec.resize(56);

        std::generate(dvec.begin(), dvec.end(), [&] { return dnorm(rng); });
        std::generate(ivec.begin(), ivec.end(), [&] { return iunif(rng); });
        std::generate(fvec.begin(), fvec.end(), [&] { return fnorm(rng); });
    }

    std::vector<double> dvec;
    std::vector<int> ivec;
    std::vector<float> fvec;
};

BENCHMARK_F(fixture, BM_irate_zip)(benchmark::State& state)
{
    double sum;
    for (auto _ : state)
    {
        sum = 0.0;
        for (auto [x, y, z] : irate::zip(dvec, ivec, fvec))
        {
            sum += x + y + z;
            benchmark::DoNotOptimize(sum);
        }
    }
    state.counters["sum"] = sum;
}

BENCHMARK_F(fixture, BM_range_v3_zip)(benchmark::State& state)
{
    double sum;
    for (auto _ : state)
    {
        sum = 0.0;
        for (auto [x, y, z] : ranges::view::zip(dvec, ivec, fvec))
        {
            sum += x + y + z;
            benchmark::DoNotOptimize(sum);
        }
    }
    state.counters["sum"] = sum;
}

BENCHMARK_F(fixture, BM_loop)(benchmark::State& state)
{
    double sum;
    for (auto _ : state)
    {
        const auto n = std::min({dvec.size(), ivec.size(), fvec.size()});

        sum = 0.0;
        for (std::size_t i = 0; i < n; ++i)
        {
            const auto x = dvec[i];
            const auto y = ivec[i];
            const auto z = fvec[i];

            sum += x + y + z;
            benchmark::DoNotOptimize(sum);
        }
    }
    state.counters["sum"] = sum;
}

BENCHMARK_MAIN();
