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

double GetRandomDouble()
{
	static std::random_device rd;
	static std::mt19937 gen(rd());
	static std::uniform_real_distribution<double> distrib(1.0, MAX_VALUE);

	return distrib(gen);
}

std::vector<double> GenerateCoefficients(std::size_t size)
{
	std::vector<double> coefficients(size);

	for (auto& element : coefficients)
	{
		element = GetRandomDouble();
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

