#pragma once

#include <ostream>

class LCGSequence
{
public:
	explicit LCGSequence(std::size_t size);
	~LCGSequence();

	std::size_t Size() const;

	int_fast64_t& operator[](std::size_t index);
	const int_fast64_t& operator[](std::size_t index) const;

	friend bool operator==(const LCGSequence& lhs, const LCGSequence& rhs);
	friend bool operator!=(const LCGSequence& lhs, const LCGSequence& rhs);

	friend std::ostream& operator<<(std::ostream& stream, const LCGSequence& sequence);

private:
	std::size_t size;
	int_fast64_t* values;
};

