#include "LCG.h"

LCG::LCG(int_fast64_t a, int_fast64_t c, int_fast64_t m)
	: a(a)
	, c(c)
	, m(m)
{}

int_fast64_t LCG::GetNext(int_fast64_t current)
{
	return (a * current + c) % m;
}

LCGSequence LCG::GenerateSequence(int_fast64_t startValue, std::size_t size)
{
	LCGSequence sequence(size);
	sequence[0] = startValue;

	for (std::size_t i = 1; i < size; ++i)
	{
		sequence[i] = GetNext(sequence[i - 1]);
	}

	return sequence;
}

bool LCG::Verify(const LCGSequence& expectedSequence)
{
	auto startValue = expectedSequence[0];
	auto size = expectedSequence.Size();

	auto actualSequence = GenerateSequence(startValue, size);
	return actualSequence == expectedSequence;
}

std::ostream& operator<<(std::ostream& stream, const LCG& lcg)
{
	return stream << "a: " << lcg.a
		<< ", c: " << lcg.c
		<< ", m: " << lcg.m;
}

