#pragma once

#include "IOptFilter.h"

#include <immintrin.h>

class m128d_OptFilter : public IOptFilter<double, __m128d, 2>
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

	__m128d InitSum() override
	{
		return __m128d{ 0.0, 0.0 };
	}

	void UpdateSum(__m128d& sum, std::size_t index) override
	{
		__m128d inputs = { GetInput(index), GetInput(index + 1) };
		__m128d coefficients = m_coefficients[index / 2];

		__m128d res = _mm_mul_pd(inputs, coefficients);

		sum = _mm_add_pd(sum, res);
	}

	double GetSumValue(__m128d sum) override
	{
		return sum[0] + sum[1];
	}

private:
	static std::pair<std::size_t, std::size_t> GetStorageIndex(std::size_t index)
	{
		return { index / 2, index % 2 };
	}
};


