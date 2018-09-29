#include <iostream>
#include <vector>
#include <set>

using namespace std;

struct X
{
	vector<bool> bits;
	vector<int> r;

	uint32_t c;
	
	X() : bits(1024 * 1024 * 2, false), r()
	{
		bits[1] = true;
		c = 0;
		go();
	}

	bool go() {
		while (++c < bits.size() && bits[c] == false) {}
		if (c < bits.size()) {
			r.push_back(c);

			auto y = c * 2 + 1;
			if (y < bits.size() && bits[y] == false) { bits[y] = true; }
			y += c;
			if (y < bits.size() && bits[y] == false) { bits[y] = true; }

			return true;
		}
		else {
			return false;
		}
	}

	int get(size_t n)
	{
		while (r.size() < n + 1 && go()) {}

		if (r.size() >= n + 1) {
			return r[n];
		} else { return -1; }
	}
};

class DoubleLinear
{
public:
	static X x;

    static int dblLinear(int n)
    {
    	if (n < 0) { return -1; }
    	return x.get(static_cast<size_t>(n));
    }
};

X DoubleLinear::x;


void test()
{
	for (int x: {
		1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 20, 30, 50, 80, 100,
		500, 510, 520, 530, 550, 560, 565, 566, 567, 568, 569, 570, 580, 590, 
		600, 700, 800, 900, 1000, 2000, 4000, 6000, 60000,
	}) {
		cout << x << " -- " << DoubleLinear::dblLinear(x) << endl;
	}
}

int main()
{
	test();
	return 0;
}
