#pragma once

#include "m128_OptFilter.h"

#ifdef __FMA_AVAILABLE__
class fma_m128_OptFilter : public m128_OptFilter 
{
protected:
	void UpdateSum(__m128& sum, std::size_t index) override
	{
		__m128 inputs = { 0.0f, 0.0f, 0.0f, 0.0f };
		for (std::size_t i = 0; i < 4; ++i)
		{
			inputs[0] = GetInput(index + i);
		}
		__m128 coefficients = m_coefficients[index / 4];

		sum = _mm_fmadd_ps(inputs, coefficients, sum);
	}
};
#endif

