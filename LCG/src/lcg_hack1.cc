#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>
#include <atomic>
#include <thread>
#include <mutex>
#include <set>

std::vector<std::pair<int_fast64_t, int_fast64_t>> PrintPossible(int_fast64_t* x)
{
	std::vector<std::pair<int_fast64_t, int_fast64_t>> result;
	std::set<int_fast64_t> as;

	for (int i = 1; i < 3; ++i)
	{
		for (int j = i + 1; j < 4; ++j)
		{
			auto sum1 = std::abs(x[i] - x[j]);
			auto sum2 = std::abs(x[i - 1] - x[j - 1]);

			as.insert(sum1 / sum2);
			as.insert(sum2 / sum1);
		}
	}

	for (auto& a : as)
	{
		for (int i = 1; i < 4; ++i)
		{
			auto c = x[i] - a * x[i - 1];

			result.emplace_back(a, c);
			result.emplace_back(a, std::abs(c));
		}
	}

	return result;
}

int main()
{
	std::ifstream fin("in.txt");

	int_fast64_t x[4] = { 0, 0, 0, 0 };
	int_fast64_t maxX = 0;

	for (int i = 0; i < 4; ++i)
	{
		fin >> x[i];
		maxX = std::max(x[i], maxX);
	}

	fin.close();

	auto pairs = PrintPossible(x);

	std::cout << pairs.size() << '\n';

	constexpr int_fast64_t threshold = 65535;

	const auto full = (threshold - maxX - 1) * (threshold - maxX - 1) * (threshold - maxX - 1);
	int_fast64_t current = 0;
	std::mutex printMutex;

	auto test = [&](auto a, auto c, auto m)
	{
		{
			/* std::lock_guard<std::mutex> guard(printMutex); */
			++current;
			std::cout << current << '/' << full << '\r';
		}
		// test
		{
			bool failed = false;
			auto prev = x[0];
			for (int i = 1; i < 4; ++i)
			{
				prev = (a * prev + c) % m;

				if (prev != x[i])
				{
					failed = true;
					break;
				}
			}

			if (failed)
			{
				return;
			}
		}

		/* std::lock_guard<std::mutex> guard(printMutex); */
		std::cout << "a: " << a << ", c: " << c << ", m: " << m << ", x_4: " << ((a * x[2] + c) % m) << '\n';
	};

	for (int_fast64_t m = maxX + 1; m <= threshold; ++m)
	{
		for (int_fast64_t a = 0; a < m; ++a)
		{
			for (int_fast64_t c = 0; c < m; ++c)
			{
				test(a, c, m);

				if (current >= 50'000)
				{
					return 0;
				}
			}
			/* int_fast64_t c = 0; */
			/* for (; c < m; c += 8) */
			/* { */
			/* 	std::thread t1(test, a, c, m); */
			/* 	std::thread t2(test, a, c+1, m); */
			/* 	std::thread t3(test, a, c+2, m); */
			/* 	std::thread t4(test, a, c+3, m); */
			/* 	std::thread t12(test, a, c+4, m); */
			/* 	std::thread t22(test, a, c+5, m); */
			/* 	std::thread t32(test, a, c+6, m); */
			/* 	std::thread t42(test, a, c+7, m); */

			/* 	t1.join(); */
			/* 	t2.join(); */
			/* 	t3.join(); */
			/* 	t4.join(); */
			/* 	t12.join(); */
			/* 	t22.join(); */
			/* 	t32.join(); */
			/* 	t42.join(); */

			/* 	if (current >= 50'000) */
			/* 	{ */
			/* 		return 0; */
			/* 	} */
			/* } */
		}
		/* for (auto [a, c] : pairs) */
		/* { */
		/* } */
	}
}

int main1()
{
	int_fast32_t x[4] = { 0, 0, 0, 0 };
	int_fast32_t maxX = 0;
	for (int i = 0; i < 4; ++i)
	{
		std::cin >> x[i];
		maxX = std::max(x[i], maxX);
	}

	//constexpr int_fast64_t threshold = 65535;

	int_fast64_t det = x[0] * x[2] + x[1] * x[3]
			 + x[1] * x[2] - x[2] * x[2]
			 - x[0] * x[3] - x[1] * x[1];

	det = std::abs(det);

	std::cout << "det: " << det << '\n';

	std::vector<int_fast64_t> modules;

	if (det != 0)
	{
		int_fast64_t low = 1;
		int_fast64_t high = det - 1;
		//auto low = det / threshold + 1;
		//auto high = det / maxX;

		for (int_fast64_t k = low; k < high; ++k)
		{
			auto res = det / k;
			if (det == res * k)
			{
				modules.push_back(res);
			}
		}
	}

	for (auto& m : modules)
	{
		auto top = std::min(x[1] - x[2], x[0] - x[1]);
		auto bottom = std::max(x[1] - x[2], x[0] - x[1]);

		int_fast64_t a = (top / bottom) % m;
		int_fast64_t c = (x[1] - a * x[0]) % m;

		// test
		{
			bool failed = false;
			auto prev = x[0];
			for (int i = 1; i < 4; ++i)
			{
				prev = (a * prev + c) % m;

				if (prev != x[1])
				{
					failed = true;
					break;
				}
			}

			if (failed)
			{
				//std::cout << "test failed (a: " << a << ", c: " << c << ", m: " << m << ")\n";
				continue;
			}
		}

		std::cout << "a: " << a << ", c: " << c << ", m: " << m << ", x_4: " << ((a * x[2] + c) % m) << '\n';
	}

	return 0;
}

