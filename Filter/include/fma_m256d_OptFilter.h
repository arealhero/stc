#pragma once

#include "m256d_OptFilter.h"

#ifdef __FMA_AVAILABLE__
class fma_m256d_OptFilter : public m256d_OptFilter 
{
protected:
	void UpdateSum(__m256d& sum, std::size_t index) override
	{
		__m256d inputs = { 0.0f, 0.0f, 0.0f, 0.0f };
		for (std::size_t i = 0; i < 4; ++i)
		{
			inputs[0] = GetInput(index + i);
		}
		__m256d coefficients = m_coefficients[index / 4];

		sum = _mm256_fmadd_pd(inputs, coefficients, sum);
	}
};
#endif

