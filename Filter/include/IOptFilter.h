#pragma once

#include "IFilter.h"

#include <cstring>

template<typename ValueType, typename OptType, std::size_t PackSize>
class IOptFilter : public IFilter<ValueType>
{
public:
	void Init(const std::vector<ValueType>& coefficients) override
	{
		m_inputsSize = coefficients.size();
		m_offset = 0;

		std::size_t rem = (m_inputsSize % PackSize > 0) ? 1 : 0;
		m_coefficientsSize = (m_inputsSize / PackSize + rem) * PackSize;

		m_coefficients = new OptType[m_coefficientsSize];
		m_inputs = new ValueType[m_inputsSize];

		memset(m_coefficients, 0, m_coefficientsSize * sizeof(OptType));
		memset(m_inputs, 0, m_inputsSize * sizeof(ValueType));

		for (std::size_t i = 0; i < m_inputsSize; ++i)
		{
			SetCoefficient(i, coefficients[i]);
		}
	}

	~IOptFilter()
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

	ValueType GetNext(ValueType input) override
	{
		PushInput(input);

		auto sum = InitSum();

		for (std::size_t i = 0; i < m_inputsSize; i += PackSize)
		{
			UpdateSum(sum, i);
		}

		return GetSumValue(sum);
	}

	std::size_t GetSize() const override
	{
		return m_inputsSize;
	}

	std::vector<ValueType> GetCoefficients() const override
	{
		std::vector<ValueType> coefficients(m_inputsSize);

		for (std::size_t i = 0; i < m_inputsSize; ++i)
		{
			coefficients[i] = GetCoefficient(i);
		}

		return coefficients;
	}

protected:
	std::size_t m_inputsSize;
	std::size_t m_coefficientsSize;
	std::size_t m_offset;

	OptType* m_coefficients;
	ValueType* m_inputs;

	ValueType GetInput(std::size_t i) const
	{
		const auto index = (m_inputsSize + i - m_offset) % m_inputsSize;
		return m_inputs[index];
	}
	void PushInput(ValueType value)
	{
		m_inputs[m_inputsSize - m_offset - 1] = value;
		m_offset = (m_offset + 1) % m_inputsSize;
	}

	virtual void SetCoefficient(std::size_t index, ValueType value) = 0;
	virtual ValueType GetCoefficient(std::size_t index) const = 0;

	virtual OptType InitSum() = 0;
	virtual void UpdateSum(OptType& sum, std::size_t index) = 0;
	virtual ValueType GetSumValue(OptType sum) = 0;
};

