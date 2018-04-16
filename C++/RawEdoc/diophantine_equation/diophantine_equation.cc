//
// x^2 - 4 * y^2 = n
//

#include <iostream>
#include <vector>
#include <utility>
#include <stdexcept>
#include <algorithm>
#include <cassert>

template<typename T1, typename T2>
std::ostream& operator<< (std::ostream& os, const std::pair<T1, T2> duo)
{
	os << "(" << duo.first << ", " << duo.second << ")";
	return os;
}

template<typename T>
std::ostream& operator<< (std::ostream& os, const std::vector<T>& vec)
{
	os << "< ";
	for (auto one: vec) {
		os << one << ", ";
	}
	os << " >";
	return os;
}

class Dioph
{
public:
	static std::vector<std::pair <long, long>> solEquaStr(long long n);
	static std::vector<std::pair <long, long>> fastSolEquaStr(long long n);
};

using namespace std;

vector<pair <long, long>> Dioph::solEquaStr(long long n)
{
	// x^2 - 4 * y^2 = n

	vector<pair<long, long>> results;
	long long prev_b = n;
	for (long long a = 1; a < prev_b; ++a) {
		auto b = n / a;
		if (a * b == n) {
			prev_b = b;
			if (!((b - a) & 3)) {
				auto x = (b + a) >> 1;
				auto y = (b - a) >> 2;
				results.push_back({x, y});
			}
		}
	}

	return results;
}

// prime factorisation
vector<pair <int, int>> factorise(long long number)
{
	vector<pair<int, int>> results;

	for (auto f = 2; f * f <= number; ++f) {
		auto counter = 0;
		while (number % f == 0) {
			++counter;
			number /= f;
		}
		if (counter) {
			results.push_back({f, counter});
		}
	}

	if (number > 1) {
		results.push_back({number, 1});
	}

	return results;
}

// num: number of factors to select
bool fill(vector<pair<int, int>>& factors, vector<int>& selection, int num)
{
	if (num > 0) {
		if (selection.size() == 0) {
			selection.push_back(0);
			--factors[0].second;
			--num;
		}
		auto index = selection.back();
		while (num > 0 && index < factors.size()) {
			if (factors[index].second > 0) {
				selection.push_back(index);
				--factors[index].second;
				--num;
			}
			else {
				++index;
			}
		}
	}
	return num == 0;
}

vector<pair <long, long>> Dioph::fastSolEquaStr(long long n)
{
	vector<pair<long, long>> results;

	if (n < 0) {
		return results;
	}

	if (((n - 1) & 3) == 0) {
		results.push_back({(n + 1) >> 1, (n - 1) >> 2});
	}

	auto factors = factorise(n);
	int total_factors = 0;
	for (auto duo: factors) {
		total_factors += duo.second;
	}

	for (auto i = 1; i < total_factors; ++i) {
		cout << " == " << i << endl;

		vector<int> x;

		// init
		if (fill(factors, x, i) == false) {
			throw logic_error("initial fill failed!");
		}

		// walk
		while (i) {
			{
				cout << " -- \t" << x << endl;
				long long a = 1;
				for (auto index: x) {
					a *= factors[index].first;
				}
				auto b = n / a;
				if (a < b && !((b - a) & 3)) {
					auto x = (b + a) >> 1;
					auto y = (b - a) >> 2;
					results.push_back({x, y});
				}
			}

			while (true) {
				auto index = x.back();
				x.pop_back();
				++factors[index].second;

				++index;

				if (index < factors.size()) {
					x.push_back(index);
					--factors[index].second;

					if (fill(factors, x, i - x.size()) == false) {
						// TODO x is now in an ill state
						// fortunately, it is going to be discarded
						cerr << "fill failed!" << endl;
						cerr << " .. \t" << x << endl;
						continue;
					}
					break;
				}
				else if (x.size() > 0){
					continue; // pop one more
				}
				else {
					cerr << "no more factors" << endl;
					goto return_factors;
				}
			}
		}

		// return factors
		return_factors:
		for (auto k: x) {
			++factors[k].second;
		}
	}

	sort(results.begin(), results.end(), std::greater<decltype(results)::value_type>());

	return results;
}

inline void test(const long long number, const vector<pair<long, long>> &expectation)
{
	auto results = Dioph::solEquaStr(number);
	if (results != expectation) {
		cerr << "for number " << number << endl
			<< " result: \t" << results << endl
			<< " expect: \t" << expectation << endl;

		assert(false);
	}
}

void test_suite()
{
	// 5 --> [[3, 1]]
	// 9001 --> [[4501, 2250]]
	// 90005 --> [[45003, 22501], [9003, 4499], [981, 467], [309, 37]
	// 90002 --> []
	test(5, {{3, 1}});
	test(9001, {{4501, 2250}});
	test(90005, {{45003, 22501}, {9003, 4499}, {981, 467}, {309, 37}});
	test(90002, {});

	// 90000001 --> [[45000001, 22500000], [6428575, 3214284], [3461545, 1730766], [494551, 247230]]
	test(90000001, {{45000001, 22500000}, {6428575, 3214284}, {3461545, 1730766}, {494551, 247230}});
}

int main()
{
	// test_suite();

	// test(1635339476, {});
	// vector<pair<int, int>> factors = factorise(1800); //(1635339476);
	// cout << factors << endl;

	// 1635339476
	// 1316629008
	// -399614547

	cout << Dioph::solEquaStr(-399614547) << endl;
	cout << Dioph::fastSolEquaStr(-399614547) << endl;

	return 0;
}

