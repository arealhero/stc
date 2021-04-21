#pragma once

#include "IOptFilter.h"

#include <immintrin.h>
#include <cstring>

class m256d_OptFilter : public IOptFilter<double, __m256d, 4>
{
public:
	using IOptFilter::IOptFilter;

protected:
	void SetCoefficient(std::size_t index, double value) override
	{
		const auto [i, j] = GetStorageIndex(index);
		m_coefficients[i][j] = value;
	}

	double GetCoefficient(std::size_t index) const override
	{
		const auto [i, j] = GetStorageIndex(index);
		return m_coefficients[i][j];
	}

	// TODO: remove { 0.0, 0.0, ... }
	__m256d InitSum() override
	{
		return __m256d{ 0.0, 0.0, 0.0, 0.0 };
	}

	void UpdateSum(__m256d& sum, std::size_t index) override
	{
		__m256d inputs;
		memset(&inputs, 0, sizeof(inputs));

		for (std::size_t i = 0; i < 4; ++i)
		{
			inputs[i] = GetInput(index + i);
		}

		__m256d coefficients = m_coefficients[index / 4];

		__m256d res = _mm256_mul_pd(inputs, coefficients);

		sum = _mm256_add_pd(sum, res);
	}

	double GetSumValue(__m256d sum) override
	{
		double result = 0.0;
		for (std::size_t i = 0; i < 4; ++i)
		{
			result += sum[i];
		}
		return result;
	}

private:
	static std::pair<std::size_t, std::size_t> GetStorageIndex(std::size_t index)
	{
		return { index / 4, index % 4 };
	}
};


