#include <iostream>
#include <vector>
#include <set>
#include <list>
#include <algorithm>
#include <limits>

using namespace std;

struct Item
{
	uint32_t i;
	uint32_t v;

	Item(uint32_t i, uint32_t v) : i(i), v(v) {}
};

struct X
{
	list<uint32_t> f;
	uint32_t ei;

	list<uint32_t> u {};
	list<Item> iu {};
	uint32_t ni {0};
	
	explicit X(const set<uint32_t>& factors, size_t expect_index) :
		f(factors.begin(), factors.end()), ei(expect_index)
	{
		iu.emplace_back(0, 1);
		ni = 1;
	}

	bool stride() {
		if (iu.empty()) {
			if (u.empty()) { return false; }
			else {
				iu.emplace_back(ni++, u.front());
				u.pop_front();
				if (ni > ei) { return true; }
			}
		}

		const auto item = iu.front();
		iu.pop_front();

		uint32_t nv = item.v * f.front() + 1;
		while (u.size() && u.front() < nv) {
			iu.emplace_back(ni++, u.front());
			u.pop_front();
			if (ni > ei) { return true; }
		}

		// TODO enhance the logic
		list<uint32_t> nl;
		for (const auto& fi : f) {
			uint32_t nv = item.v * fi + 1;
			nl.emplace_back(nv);
		}

		u.merge(nl);

		return true;
	}

	uint32_t get()
	{
		while (ni <= ei && stride()) {}

		if (ni > ei) {
			for (auto rit = iu.crbegin(); rit != iu.crend(); ++rit) {
				// cout << "Item: " << rit->i << " | " << rit->v << endl;
				if (rit->i == ei) { return rit->v; }
			}
		}

		throw logic_error("Cannot find!");
	}
};

uint32_t n_linear(const std::set<uint32_t>& factors, size_t n)
{
	// cout << " ~~ ";
	// for (const auto& fi: factors) {
	// 	cout << fi << ", ";
	// }
	// cout << " ~~ " << n << endl;

    X x(factors, n);
    return x.get();
}

void test()
{
	cout << n_linear({2,3}, 0) << endl;
	cout << n_linear({2,3}, 1) << endl;
	cout << n_linear({2,3}, 2) << endl;

	cout << n_linear({2,3}, 10) << endl;
	cout << n_linear({3,2}, 10) << endl;

	cout << n_linear({5, 7, 8}, 10) << endl;
	cout << n_linear({5, 7, 8}, 11) << endl;

	cout << n_linear({2, 6}, 416) << endl;

	cout << n_linear({2, 3}, 200000) << endl; // 133028635

	cout << n_linear({10, 13}, 741) << endl; // 3172655773
	// 3172655773
	// 2468256519

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
