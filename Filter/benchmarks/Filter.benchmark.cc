#include <benchmark/benchmark.h>

#include <OptFilter.h>
#include <UnoptFilter.h>

#include <Utils.h>

static void BM_OptFilter(benchmark::State& state)
{
	for (auto _ : state)
	{
		state.PauseTiming();
		auto coefficients = GenerateCoefficients(state.range(0));
		Filter filter = Make<OptFilter>(coefficients);
		auto inputs = GenerateCoefficients(state.range(0));
		state.ResumeTiming();

		for (auto input : inputs)
		{
			auto output = filter->GetNext(input);
			benchmark::DoNotOptimize(output);
		}
	}
}
BENCHMARK(BM_OptFilter)
	->Args({ 1 << 1 })
	->Args({ 1 << 2 })
	->Args({ 1 << 4 })
	->Args({ 1 << 8 });

static void BM_UnoptFilter(benchmark::State& state)
{
	for (auto _ : state)
	{
		state.PauseTiming();
		auto coefficients = GenerateCoefficients(state.range(0));
		Filter filter = Make<UnoptFilter>(coefficients);
		auto inputs = GenerateCoefficients(state.range(0));
		state.ResumeTiming();

		for (auto input : inputs)
		{
			auto output = filter->GetNext(input);
			benchmark::DoNotOptimize(output);
		}
	}
}
BENCHMARK(BM_UnoptFilter)
	->Args({ 1 << 1 })
	->Args({ 1 << 2 })
	->Args({ 1 << 4 })
	->Args({ 1 << 8 });

BENCHMARK_MAIN();

