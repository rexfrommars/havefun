#include <iostream>
#include <vector>
#include <set>
#include <list>
#include <algorithm>

using namespace std;

struct X
{
	list<uint32_t> f;

	vector<bool> bits;
	vector<int> r;

	uint32_t c;
	uint32_t d;
	
	explicit X(const set<uint32_t>& factors) :
		f(factors.begin(), factors.end()),
		bits(1024 * 1024 * 1024, false), r()
	{
		bits[1] = true;
		c = 0;
		d = 0;
		stride();
	}

	bool stride() {
		while (++c < bits.size() && bits[c] == false) {}
		if (c < bits.size()) {
			uint32_t y = 0;

#if 0
			r.push_back(c);
#else
			y = c * f.front() + 1;
			for (; d < y && d < bits.size(); ++d) {
				if (bits[d]) {
					r.push_back(d);
				}
			}
#endif

			// cout << "result: " << r.size() - 1 << " | " << r.back() << endl;

			for (auto fi: f) {
				y = c * fi + 1;
				if (y < bits.size()) {
					bits[y] = true;
				}
				else { return false; }
			}

			return true;
		}
		else {
			return false;
		}
	}

	uint32_t get(size_t n)
	{
		while (r.size() < n + 1 && stride()) {}

		if (r.size() >= n + 1) {
			return r[n];
		} else { return -1; }
	}
};

uint32_t n_linear(const std::set<uint32_t>& factors, size_t n)
{
	for (const auto& fi: factors) {
		cout << fi << ", ";
	}
	cout << endl;

    X x(factors);
    return x.get(n);
}

void test()
{
	cout << n_linear({2,3}, 10) << endl;
	cout << n_linear({3,2}, 10) << endl;

	cout << n_linear({5, 7, 8}, 10) << endl;
	cout << n_linear({5, 7, 8}, 11) << endl;

	cout << n_linear({2, 6}, 416) << endl;

	//cout << n_linear({2, 3}, 2000000) << endl; // 133028635

	cout << n_linear({10, 13}, 741) << endl; // 3172655773
	// 3172655773
	// 883708281

	return;

	cout << n_linear({2, 3}, 2000000) << endl; // 133028635
	cout << n_linear({2, 3, 10000002}, 2000000) << endl; // 133028307

	cout << n_linear({2, 3, 5}, 419547) << endl; // 7699756

}

int main()
{
	test();
	return 0;
}
