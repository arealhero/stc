#include <gtest/gtest.h>

#include <limits>

#include <OptFilter.h>
#include <UnoptFilter.h>
#include <Utils.h>

TEST(Filter, Constructor)
{
	for (std::size_t size = 1; size < MAX_SIZE; ++size)
	{
		auto coefficients = GenerateCoefficients(size);

		Filter optFilter = Make<OptFilter>(coefficients);
		Filter unoptFilter = Make<UnoptFilter>(coefficients);

		ASSERT_EQ(optFilter, unoptFilter);
	}
}

TEST(Filter, GetNext)
{
	for (std::size_t size = 1; size < MAX_SIZE; ++size)
	{
		auto coefficients = GenerateCoefficients(size);
		// TODO: rename GenerateCoefficients
		auto inputs = GenerateCoefficients(2 * size);

		Filter optFilter = Make<OptFilter>(coefficients);
		Filter unoptFilter = Make<UnoptFilter>(coefficients);

		for (auto input : inputs)
		{
			auto optOut = optFilter->GetNext(input);
			auto unoptOut = unoptFilter->GetNext(input);

			ASSERT_DOUBLE_EQ(unoptOut, optOut);
		}
	}
}

int main(int argc, char* argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

