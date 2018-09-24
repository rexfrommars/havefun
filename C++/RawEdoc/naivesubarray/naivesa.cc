#include <iostream>
#include <iomanip>
#include <array>

using namespace std;


template <class T, std::size_t N>
struct _Stat
{
	std::string name;

	std::array<T, N> table {};

	int c {};
	int ec {};

	explicit _Stat(std::string && name) : name(name) {}

	constexpr size_t size() const { return N; }

	void adjust(int x) {
		if (table[x] & 0x1) { --ec; }
		else { ++ec; }
	}

	bool add(int x) {
		++c;
		++table[x];
		if (table[x] > 1) { adjust(x); }
		return true;
	}

	bool remove(int x) {
		if (table[x] == 0) {
			return false;
		}

		--c;
		--table[x];
		if (table[x] > 0) { adjust(x); }
		return true;
	}

	const T& operator[] (size_t x) const { return table[x]; }
};

template <class T, size_t N>
ostream& operator << (ostream& os, const _Stat<T, N> & s)
{
	os << s.name << " : " << s.ec << " / " << s.c;
	return os;
}

using Stat = _Stat<int, 512>;

int _solve(int* p, size_t len)
{
	cout << "len: " << len << endl;

	int result = 0;

	Stat sa("stat-A");
	Stat sb("stat-B");
	for(size_t c = 0; c < len; ++c) {
		int i = p[c];
		sa.add(i);
		cout << " [" << c << "] " << i << " : " << sa[i] << " | : " << sa.ec << endl;
	}
	cout << "even_count: " << sa.ec << endl;

	Stat* sx = &sa;
	Stat* sy = &sb;
	for (; len > 1; len -= 2, ++p) {
		cout << "-----------------" << *p << endl;
		cout << "sx: " << *sx << endl;
		cout << "sy: " << *sy << endl;

		if (sx->ec == 0) { ++result; }

		for (size_t c = len - 1; c; --c) {
			int i = p[c];
			sx->remove(i);
			sy->add(i);
			cout << " ---- " << i << " || " << *sx << " | " << *sy << endl;
			if (sx->ec == 0) { ++result; }
			if (sy->ec == 0) { ++result; }
		}

		sx->remove(p[0]);
		sy->remove(p[len - 1]);

		swap(sx, sy);
	}

	result += len; // if (len == 1) { ++result; }

	return result;
}

template<std::size_t S>
int solve(std::array<int, S> a) {
 	return _solve(a.data(), S);
}

void test()
{
	std::array<int, 15> a = {2, 5, 2, 3, 6, 7, 8, 23, 23, 13, 65, 31, 3, 4, 3}; // 53
	//std::array a = {6,1,7,4,6,7,1,4,7,1,4,6,6,7,4,1,6,4,7,1,4,5,3,2,1,6,9}; // 114

	int result = solve(a);
	cout << "result: " << result << endl;
}

int main()
{
	test();
	return 0;
}

