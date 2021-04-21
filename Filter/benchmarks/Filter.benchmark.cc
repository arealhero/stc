#include <benchmark/benchmark.h>

#include <m128_OptFilter.h>
#include <m128d_OptFilter.h>
#include <m256_OptFilter.h>
#include <m256d_OptFilter.h>

#include <fma_m128_OptFilter.h>
#include <fma_m128d_OptFilter.h>
#include <fma_m256_OptFilter.h>
#include <fma_m256d_OptFilter.h>

#include <UnoptFilter.h>

#include <Utils.h>

// TODO: refactor benchmarks

static void BM_m128d_OptFilter(benchmark::State& state)
{
	for (auto _ : state)
	{
		state.PauseTiming();
		auto coefficients = GenerateCoefficients(state.range(0));
		Filter<double> filter = MakeFilter<m128d_OptFilter>(coefficients);
		auto inputs = GenerateCoefficients(state.range(0));
		state.ResumeTiming();

		for (auto input : inputs)
		{
			auto output = filter->GetNext(input);
			benchmark::DoNotOptimize(output);
		}
	}
}
BENCHMARK(BM_m128d_OptFilter)
	->Args({ 1 << 1 })
	->Args({ 1 << 2 })
	->Args({ 1 << 4 })
	->Args({ 1 << 8 });

static void BM_m256d_OptFilter(benchmark::State& state)
{
	for (auto _ : state)
	{
		state.PauseTiming();
		auto coefficients = GenerateCoefficients(state.range(0));
		Filter<double> filter = MakeFilter<m256d_OptFilter>(coefficients);
		auto inputs = GenerateCoefficients(state.range(0));
		state.ResumeTiming();

		for (auto input : inputs)
		{
			auto output = filter->GetNext(input);
			benchmark::DoNotOptimize(output);
		}
	}
}
BENCHMARK(BM_m256d_OptFilter)
	->Args({ 1 << 1 })
	->Args({ 1 << 2 })
	->Args({ 1 << 4 })
	->Args({ 1 << 8 });

static void BM_m256_OptFilter(benchmark::State& state)
{
	for (auto _ : state)
	{
		state.PauseTiming();
		auto coefficients = GenerateCoefficients<float>(state.range(0));
		Filter<float> filter = MakeFilter<m256_OptFilter>(coefficients);
		auto inputs = GenerateCoefficients<float>(state.range(0));
		state.ResumeTiming();

		for (auto input : inputs)
		{
			auto output = filter->GetNext(input);
			benchmark::DoNotOptimize(output);
		}
	}
}
BENCHMARK(BM_m256_OptFilter)
	->Args({ 1 << 1 })
	->Args({ 1 << 2 })
	->Args({ 1 << 4 })
	->Args({ 1 << 8 });

static void BM_m128_OptFilter(benchmark::State& state)
{
	for (auto _ : state)
	{
		state.PauseTiming();
		auto coefficients = GenerateCoefficients<float>(state.range(0));
		Filter<float> filter = MakeFilter<m128_OptFilter>(coefficients);
		auto inputs = GenerateCoefficients<float>(state.range(0));
		state.ResumeTiming();

		for (auto input : inputs)
		{
			auto output = filter->GetNext(input);
			benchmark::DoNotOptimize(output);
		}
	}
}
BENCHMARK(BM_m128_OptFilter)
	->Args({ 1 << 1 })
	->Args({ 1 << 2 })
	->Args({ 1 << 4 })
	->Args({ 1 << 8 });

#ifdef __FMA_AVAILABLE__
static void BM_fma_m128d_OptFilter(benchmark::State& state)
{
	for (auto _ : state)
	{
		state.PauseTiming();
		auto coefficients = GenerateCoefficients(state.range(0));
		Filter<double> filter = MakeFilter<fma_m128d_OptFilter>(coefficients);
		auto inputs = GenerateCoefficients(state.range(0));
		state.ResumeTiming();

		for (auto input : inputs)
		{
			auto output = filter->GetNext(input);
			benchmark::DoNotOptimize(output);
		}
	}
}
BENCHMARK(BM_fma_m128d_OptFilter)
	->Args({ 1 << 1 })
	->Args({ 1 << 2 })
	->Args({ 1 << 4 })
	->Args({ 1 << 8 });

static void BM_fma_m256d_OptFilter(benchmark::State& state)
{
	for (auto _ : state)
	{
		state.PauseTiming();
		auto coefficients = GenerateCoefficients(state.range(0));
		Filter<double> filter = MakeFilter<fma_m256d_OptFilter>(coefficients);
		auto inputs = GenerateCoefficients(state.range(0));
		state.ResumeTiming();

		for (auto input : inputs)
		{
			auto output = filter->GetNext(input);
			benchmark::DoNotOptimize(output);
		}
	}
}
BENCHMARK(BM_fma_m256d_OptFilter)
	->Args({ 1 << 1 })
	->Args({ 1 << 2 })
	->Args({ 1 << 4 })
	->Args({ 1 << 8 });

static void BM_fma_m128_OptFilter(benchmark::State& state)
{
	for (auto _ : state)
	{
		state.PauseTiming();
		auto coefficients = GenerateCoefficients<float>(state.range(0));
		Filter<float> filter = MakeFilter<fma_m128_OptFilter>(coefficients);
		auto inputs = GenerateCoefficients<float>(state.range(0));
		state.ResumeTiming();

		for (auto input : inputs)
		{
			auto output = filter->GetNext(input);
			benchmark::DoNotOptimize(output);
		}
	}
}
BENCHMARK(BM_fma_m128_OptFilter)
	->Args({ 1 << 1 })
	->Args({ 1 << 2 })
	->Args({ 1 << 4 })
	->Args({ 1 << 8 });

static void BM_fma_m256_OptFilter(benchmark::State& state)
{
	for (auto _ : state)
	{
		state.PauseTiming();
		auto coefficients = GenerateCoefficients<float>(state.range(0));
		Filter<float> filter = MakeFilter<fma_m256_OptFilter>(coefficients);
		auto inputs = GenerateCoefficients<float>(state.range(0));
		state.ResumeTiming();

		for (auto input : inputs)
		{
			auto output = filter->GetNext(input);
			benchmark::DoNotOptimize(output);
		}
	}
}
BENCHMARK(BM_fma_m256_OptFilter)
	->Args({ 1 << 1 })
	->Args({ 1 << 2 })
	->Args({ 1 << 4 })
	->Args({ 1 << 8 });
#endif

static void BM_DoubleUnoptFilter(benchmark::State& state)
{
	for (auto _ : state)
	{
		state.PauseTiming();
		auto coefficients = GenerateCoefficients(state.range(0));
		Filter<double> filter = MakeFilter<DoubleUnoptFilter>(coefficients);
		auto inputs = GenerateCoefficients(state.range(0));
		state.ResumeTiming();

		for (auto input : inputs)
		{
			auto output = filter->GetNext(input);
			benchmark::DoNotOptimize(output);
		}
	}
}
BENCHMARK(BM_DoubleUnoptFilter)
	->Args({ 1 << 1 })
	->Args({ 1 << 2 })
	->Args({ 1 << 4 })
	->Args({ 1 << 8 });

static void BM_FloatUnoptFilter(benchmark::State& state)
{
	for (auto _ : state)
	{
		state.PauseTiming();
		auto coefficients = GenerateCoefficients<float>(state.range(0));
		Filter<float> filter = MakeFilter<FloatUnoptFilter>(coefficients);
		auto inputs = GenerateCoefficients<float>(state.range(0));
		state.ResumeTiming();

		for (auto input : inputs)
		{
			auto output = filter->GetNext(input);
			benchmark::DoNotOptimize(output);
		}
	}
}
BENCHMARK(BM_FloatUnoptFilter)
	->Args({ 1 << 1 })
	->Args({ 1 << 2 })
	->Args({ 1 << 4 })
	->Args({ 1 << 8 });

BENCHMARK_MAIN();

