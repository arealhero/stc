#pragma once

#include "IFilter.h"

template<typename ValueType>
class UnoptFilter : public IFilter<ValueType>
{
public:
	void Init(const std::vector<ValueType>& coefficients) override
	{
		m_coefficients = coefficients;
		m_inputs.resize(coefficients.size(), 0);
		m_offset = 0;
	}

	~UnoptFilter() override = default;

	ValueType GetNext(ValueType input) override
	{
		std::size_t size = GetSize();

		m_inputs[size - m_offset - 1] = input;
		m_offset = (m_offset + 1) % size;

		ValueType sum = 0;
		for (std::size_t i = 0; i < size; ++i)
		{
			auto index = (size + i - m_offset) % size;
			sum += m_coefficients[i] * m_inputs[index];
		}

		return sum;
	}

	std::size_t GetSize() const override
	{
		return m_coefficients.size();
	}

	std::vector<ValueType> GetCoefficients() const override
	{
		return m_coefficients;
	}

private:
	std::vector<ValueType> m_coefficients;
	std::vector<ValueType> m_inputs;

	std::size_t m_offset;
};

using DoubleUnoptFilter = UnoptFilter<double>;
using FloatUnoptFilter = UnoptFilter<float>;

