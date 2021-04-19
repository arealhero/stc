#pragma once

#include "IFilter.h"

#include <xmmintrin.h>
#include <cstring>

class OptFilter : public IFilter
{
public:
	OptFilter(const std::vector<double>& coefficients)
		: m_size(coefficients.size())
		, m_offset(0)
	{
		m_coefficients = new __m128d[m_size / 2 + m_size % 2];
		m_inputs = new double[m_size];

		for (std::size_t i = 0; i < m_size; ++i)
		{
			SetCoefficient(i, coefficients[i]);
			m_inputs[i] = 0;
		}
	}

	~OptFilter() override
	{
		if (m_coefficients)
		{
			delete[] m_coefficients;
		}

		if (m_inputs)
		{
			delete[] m_inputs;
		}
	}

	// _mm_mul_ps: TODO: check performance (floats)
	double GetNext(double input) override
	{
		m_inputs[m_size - m_offset - 1] = input;
		m_offset = (m_offset + 1) % m_size;

		auto rem = m_size % 2;
		double sum = 0.0;
		for (std::size_t i = 0; i < m_size - rem; i += 2)
		{
			__m128d inputs = { GetInput(i), GetInput(i + 1) };
			__m128d coefficients = m_coefficients[i / 2];
			__m128d res = _mm_mul_pd(inputs, coefficients);

			sum += res[0];
			sum += res[1];
			/* sum = _mm_add_pd(sum, res); */
		}

		if (rem == 1)
		{
			__m128d inputs = { GetInput(m_size - 1), 0.0 };
			__m128d coefficients = m_coefficients[m_size / 2];
			__m128d res = _mm_mul_pd(inputs, coefficients);

			sum += res[0];
			/* sum = _mm_add_pd(sum, res); */
		}

		return sum;
	}

	std::size_t GetSize() const override
	{
		return m_size;
	}

	std::vector<double> GetCoefficients() const override
	{
		std::vector<double> coefficients(m_size);

		for (std::size_t i = 0; i < m_size; ++i)
		{
			coefficients[i] = GetCoefficient(i);
		}

		return coefficients;
	}

private:
	std::size_t m_size;
	std::size_t m_offset;

	__m128d* m_coefficients;
	double* m_inputs;

	// TODO: remove `if` statement
	double GetInput(std::size_t i)
	{
		/* if (i == m_size) return 0.0; */

		const auto index = (m_size + i - m_offset) % m_size;
		return m_inputs[index];
	}

	static std::pair<std::size_t, std::size_t> GetStorageIndex(std::size_t index)
	{
		return { index / 2, index % 2 };
	}

	double GetCoefficient(std::size_t index) const
	{
		const auto [i, j] = GetStorageIndex(index);
		return m_coefficients[i][j];
	}

	void SetCoefficient(std::size_t index, double value)
	{
		const auto [i, j] = GetStorageIndex(index);
		m_coefficients[i][j] = value;
	}
};

