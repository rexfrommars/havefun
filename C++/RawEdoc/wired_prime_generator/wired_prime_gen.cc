#include <iostream>
#include <vector>
#include <set>

using namespace std;

template<typename T>
ostream& operator<< (ostream& os, const vector<T>& vec)
{
	for (auto i: vec) {
		os << i << ", ";
	}
	return os;
}

static long long gcd(long long a, long long b)
{
	if (a >= b) {
		auto remainder = a % b;
		if (remainder) {
			return gcd(b, remainder);
		}
		else {
			return b;
		}
	}
	else {
		return gcd(b, a);
	}
}

static vector<long long> an(uint32_t n)
{
	vector<long long> vec;
	long long prev = 7;
	vec.push_back(prev);

	for (int i = 2; i <= n; ++i) {
		prev += gcd(i, prev);
		vec.push_back(prev);
	}

	return vec;
}

static vector<long long> gn(uint32_t n)
{
	vector<long long> results = {1};
	auto vec = an(n);
	for (int i = 1; i < vec.size(); ++i) {
		results.push_back(vec[i] - vec[i-1]);
	}

	return results;
}

static set<long long> pn(uint32_t n)
{
	set<long long> results;

	long long prev = 7;
	for (int i = 2; results.size() < n; ++i) {
		auto diff = gcd(i, prev);
		prev += gcd(i, prev);
		if (diff > 1) {
			results.insert(diff);
		}
	}

	return results;
}

static vector<long long> anOver(uint32_t n)
{
	vector<long long> results;

	long long prev = 7;
	for (int i = 2; results.size() < n; ++i) {
		auto diff = gcd(i, prev);
		prev += gcd(i, prev);
		if (diff > 1) {
			results.push_back(prev/i);
		}
	}

	return results;
}

class WeirdPrimeGen
{
public:
	static long long countOnes(long long n)
	{
		long long result = 0;
		for (auto i: gn(n)) {
			if (i == 1) {
				++result;
			}
		}
		return result;
	}

	static long long maxPn(long long n)
	{
		long long result = 0;
		for (auto i: pn(n)) {
			if (i > result) {
				result = i;
			}
		}
		return result;
	}

	static int anOverAverage(long long n)
	{
		int sum = 0;
		for (auto i: anOver(n)) {
			sum += i;
		}
		return sum / n;
	}
};


int main()
{
	cout << an(30) << endl;
	cout << gn(30) << endl;

	auto pn_result = pn(30);
	//cout << pn << endl;

	cout << anOver(10) << endl;
	cout << WeirdPrimeGen::anOverAverage(1) << endl;

	return 0;
}
