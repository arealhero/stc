#include <iostream>
#include <cstdint>

#include "LCGSequence.h"
#include "LCG.h"
#include "Utils.h"

constexpr std::size_t SEQUENCE_LEN = 4;
constexpr int_fast64_t threshold = 65535;

// TODO: probably should be removed
int_fast64_t AbsMod(int_fast64_t value, int_fast64_t mod)
{
	return value < 0 ? value + mod : value;
}

// TODO: write specs
int main()
{
	LCGSequence input(SEQUENCE_LEN);
	int_fast64_t inputMax = 0;
	for (std::size_t i = 0; i < SEQUENCE_LEN; ++i)
	{
		std::cin >> input[i];
		inputMax = std::max(inputMax, input[i]);
	}

	for (int_fast64_t m = inputMax + 1; m <= threshold; ++m)
	{
		auto diff1 = AbsMod(input[0] - input[1], m);
		auto diff2 = AbsMod(input[1] - input[2], m);

		auto u = AbsMod(FindModularInverse(diff1, m), m);
		auto a = (diff2 * u) % m;

		auto diff3 = AbsMod(input[1] - a * input[0], m);
		auto c = diff3 % m;

		LCG lcg(a, c, m);
		if (lcg.Verify(input))
		{
			std::cout << lcg << '\n' << lcg.GenerateSequence(input[0], 5);
		}
	}

}

