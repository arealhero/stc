#include "Utils.h"

// TODO: remove
#include <iostream>

int_fast64_t GetPositiveMod(int_fast64_t a, int_fast64_t m)
{
	auto mod = a % m;
	if (mod < 0)
	{
		mod += m;
	}
	return mod;
}

// Algorithm:
// https://en.wikipedia.org/wiki/Modular_multiplicative_inverse#Extended_Euclidean_algorithm
int_fast64_t FindModularInverse(int_fast64_t number, int_fast64_t modulo)
{
	int_fast64_t remainder = modulo,
		     oldRemainder = number,
		     inverse = 0,
		     oldInverse = 1,
		     copy;

	while (remainder != 0)
	{
		auto quotient = oldRemainder / remainder;

		copy = remainder;
		remainder = oldRemainder - quotient * copy;
		oldRemainder = copy;

		copy = inverse;
		inverse = oldInverse - quotient * copy;
		oldInverse = copy;
	}

	return oldInverse;
}

