#pragma once

#include "m128d_OptFilter.h"

#ifdef __FMA_AVAILABLE__
class fma_m128d_OptFilter : public m128d_OptFilter 
{
protected:
	void UpdateSum(__m128d& sum, std::size_t index) override
	{
		__m128d inputs = { GetInput(index), GetInput(index + 1) };
		__m128d coefficients = m_coefficients[index / 2];

		sum = _mm_fmadd_pd(inputs, coefficients, sum);
	}
};
#endif

