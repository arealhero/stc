#pragma once

#include <vector>
#include <random>
#include <memory>
#include <utility>

// TODO: create random generator classes

constexpr std::size_t MAX_SIZE = 100;
constexpr double MAX_VALUE = 100.0;

std::size_t GetRandomSize()
{
	static std::random_device rd;
	static std::mt19937 gen(rd());
	static std::uniform_int_distribution<std::size_t> distrib(1, MAX_SIZE);

	return distrib(gen);
}

// TODO: remove function
double GetRandomDouble()
{
	static std::random_device rd;
	static std::mt19937 gen(rd());
	static std::uniform_real_distribution<double> distrib(1.0, MAX_VALUE);

	return distrib(gen);
}

// TODO: remove default template value
template<typename ValueType = double>
std::vector<ValueType> GenerateCoefficients(std::size_t size)
{
	std::vector<ValueType> coefficients(size);

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<ValueType> distrib(1.0, MAX_VALUE);

	for (auto& element : coefficients)
	{
		element = distrib(gen);
	}

	return coefficients;
}

std::vector<double> GenerateCoefficients()
{
	const auto size = GetRandomSize();
	return GenerateCoefficients(size);
}

template<typename T, typename... Args>
std::unique_ptr<T> Make(Args&&... args)
{
	return std::make_unique<T>(std::forward<Args>(args)...);
}

template<typename T, typename... Args>
std::unique_ptr<T> MakeFilter(Args&&... args)
{
	auto filter = std::make_unique<T>();
	filter->Init(std::forward<Args>(args)...);
	return filter;
}

