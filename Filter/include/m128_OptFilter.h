#pragma once

#include "IOptFilter.h"

#include <immintrin.h>

class m128_OptFilter : public IOptFilter<float, __m128, 4>
{
public:
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

	__m128 InitSum() override
	{
		return __m128{ 0.0f, 0.0f, 0.0f, 0.0f };
	}

	void UpdateSum(__m128& sum, std::size_t index) override
	{
		__m128 inputs = { 0.0f, 0.0f, 0.0f, 0.0f };
		// TODO: remove magic number 4 (use PackSize variable somehow)
		for (std::size_t i = 0; i < 4; ++i)
		{
			inputs[i] = GetInput(index + i);
		}
		__m128 coefficients = m_coefficients[index / 4];

		__m128 res = _mm_mul_ps(inputs, coefficients);

		sum = _mm_add_ps(sum, res);
	}

	float GetSumValue(__m128 sum) override
	{
		float result = 0;
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

