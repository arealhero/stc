#pragma once

#include <vector>
#include <memory>

template<typename ValueType>
class IFilter
{
public:
	virtual ~IFilter() {}

	virtual void Init(const std::vector<ValueType>& coefficients) = 0;

	virtual ValueType GetNext(ValueType input) = 0;

	virtual std::size_t GetSize() const = 0;
	virtual std::vector<ValueType> GetCoefficients() const = 0;
};

template<typename ValueType>
using Filter = std::unique_ptr<IFilter<ValueType>>;

template<typename ValueType>
bool operator==(const Filter<ValueType>& lhs, const Filter<ValueType>& rhs)
{
	return lhs->GetCoefficients() == rhs->GetCoefficients();
}

