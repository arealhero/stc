#pragma once

#include "m256_OptFilter.h"

#ifdef __FMA_AVAILABLE__
class fma_m256_OptFilter : public m256_OptFilter 
{
protected:
	void UpdateSum(__m256& sum, std::size_t index) override
	{
		__m256 inputs = _mm256_setzero_ps();
		for (std::size_t i = 0; i < 8; ++i)
		{
			inputs[0] = GetInput(index + i);
		}
		__m256 coefficients = m_coefficients[index / 4];

		sum = _mm256_fmadd_ps(inputs, coefficients, sum);
	}
};
#endif

