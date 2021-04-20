#pragma once

#include <ostream>

#include "LCGSequence.h"

class LCG
{
public:
	LCG(int_fast64_t a, int_fast64_t c, int_fast64_t m);

	int_fast64_t GetNext(int_fast64_t current);

	LCGSequence GenerateSequence(int_fast64_t startValue, std::size_t size);

	bool Verify(const LCGSequence& expectedSequence);

	friend std::ostream& operator<<(std::ostream& stream, const LCG& lcg);

private:
	int_fast64_t a, c, m;
};

