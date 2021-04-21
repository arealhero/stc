#pragma once

#include "IOptFilter.h"

#include <immintrin.h>
#include <cstring>

class m256_OptFilter : public IOptFilter<float, __m256, 8>
{
public:
	// TODO: remove `using ...` statement from m*_OptFilter's
	using IOptFilter::IOptFilter;

protected:
	void SetCoefficient(std::size_t index, float value) override
	{
		const auto [i, j] = GetStorageIndex(index);
		m_coefficients[i][j] = value;
	}

	float GetCoefficient(std::size_t index) const override
	{
		const auto [i, j] = GetStorageIndex(index);
		return m_coefficients[i][j];
	}

	// TODO: remove { 0.0, 0.0, ... }
	__m256 InitSum() override
	{
		return _mm256_setzero_ps();
	}

	void UpdateSum(__m256& sum, std::size_t index) override
	{
		__m256 inputs = _mm256_setzero_ps();

		for (std::size_t i = 0; i < 8; ++i)
		{
			inputs[i] = GetInput(index + i);
		}

		__m256 coefficients = m_coefficients[index / 8];

		__m256 res = _mm256_mul_ps(inputs, coefficients);

		sum = _mm256_add_ps(sum, res);
	}

	float GetSumValue(__m256 sum) override
	{
		float result = 0.0;
		for (std::size_t i = 0; i < 8; ++i)
		{
			result += sum[i];
		}
		return result;
	}

private:
	static std::pair<std::size_t, std::size_t> GetStorageIndex(std::size_t index)
	{
		return { index / 8, index % 8 };
	}
};


