#include "LCGSequence.h"

LCGSequence::LCGSequence(std::size_t size)
	: size(size)
{
	values = new int_fast64_t[size];
}

LCGSequence::~LCGSequence()
{
	if (values)
	{
		delete[] values;
	}
}

std::size_t LCGSequence::Size() const
{
	return size;
}

int_fast64_t& LCGSequence::operator[](std::size_t index)
{
	return values[index];
}

const int_fast64_t& LCGSequence::operator[](std::size_t index) const
{
	return values[index];
}

bool operator==(const LCGSequence& lhs, const LCGSequence& rhs)
{
	if (lhs.size != rhs.size) return false;

	for (std::size_t i = 0; i < lhs.size; ++i)
	{
		if (lhs[i] != rhs[i])
		{
			return false;
		}
	}

	return true;
}

bool operator!=(const LCGSequence& lhs, const LCGSequence& rhs)
{
	return !(lhs == rhs);
}

std::ostream& operator<<(std::ostream& stream, const LCGSequence& sequence)
{
	for (std::size_t i = 0; i < sequence.size; ++i)
	{
		stream << "x[" << i << "]:\t" << sequence[i] << '\n';
	}
	return stream;
}

