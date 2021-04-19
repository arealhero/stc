#include <OptFilter.h>
#include <UnoptFilter.h>

#include <iostream>
#include <random>
#include <vector>

constexpr std::size_t MAX_SIZE = 30;
constexpr double MAX_VALUE = 10.0;

std::size_t GenSize()
{
	static std::random_device rd;
	static std::mt19937 gen(rd());
	static std::uniform_int_distribution<std::size_t> distrib(1, MAX_SIZE);

	auto size = distrib(gen);
	return size % 2 == 1 ? size : size + 1;
}

double GenCoefficient()
{
	static std::random_device rd;
	static std::mt19937 gen(rd());
	static std::uniform_real_distribution<double> distrib(1.0, MAX_VALUE);

	return distrib(gen);
}

std::vector<double> GenCoefficients()
{
	auto size = GenSize();

	std::cout << "COEFFS: ";
	std::vector<double> coefficients(size);
	for (auto& element : coefficients)
	{
		element = GenCoefficient();
		std::cout << element << ' ';
	}
	std::cout << '\n';

	return coefficients;
}

int main()
{
	auto coefficients = GenCoefficients();
	auto inputs = GenCoefficients();

	OptFilter optFilter(coefficients);
	UnoptFilter unoptFilter(coefficients);

	for (auto input : inputs)
	{
		auto optOut = optFilter.GetNext(input);
		auto unoptOut = unoptFilter.GetNext(input);

		if (optOut != unoptOut)
		{
			std::cout << "FAIL: values differ:\n"
				<< "input: " << input
				<< "\noptOut: " << optOut
				<< "\nunoptOut: " << unoptOut
				<< '\n';

			return 1;
		}
	}

	std::cout << "PASS\n";
	return 0;
}

