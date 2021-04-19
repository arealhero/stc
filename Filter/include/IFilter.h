#pragma once

#include <vector>
#include <memory>

class IFilter
{
public:
	virtual ~IFilter() {}

	virtual double GetNext(double input) = 0;

	virtual std::size_t GetSize() const = 0;
	virtual std::vector<double> GetCoefficients() const = 0;
};

using Filter = std::unique_ptr<IFilter>;

bool operator==(const Filter& lhs, const Filter& rhs)
{
	return lhs->GetCoefficients() == rhs->GetCoefficients();
}

