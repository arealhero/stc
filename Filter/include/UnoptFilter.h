#pragma once

#include "IFilter.h"

class UnoptFilter : public IFilter
{
public:
	UnoptFilter(const std::vector<double>& coefficients)
		: m_coefficients(coefficients)
		, m_inputs(coefficients.size(), 0)
		, m_offset(0)
	{}

	~UnoptFilter() override = default;

	double GetNext(double input) override
	{
		std::size_t size = GetSize();

		m_inputs[size - m_offset - 1] = input;
		m_offset = (m_offset + 1) % size;

		double sum = 0.0;
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

	std::vector<double> GetCoefficients() const override
	{
		return m_coefficients;
	}

private:
	std::vector<double> m_coefficients;
	std::vector<double> m_inputs;

	std::size_t m_offset;
};

