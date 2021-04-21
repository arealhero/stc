#include <benchmark/benchmark.h>

#include <m128d_OptFilter.h>
#include <fma_m128d_OptFilter.h>

#include <UnoptFilter.h>

#include <Utils.h>

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

BENCHMARK_MAIN();

