#include <iostream>

using namespace std;

//
// x _ _ 2 _ _ 3 _ 4
// _ x _ _ _ _ _ 4 _
// 1 _ x _ _ _ 4 _ 5
// _ _ _ x _ 4 _ _ _
// _ _ _ _ x _ _ _ _
// _ _ _ 4 _ x _ _ _
// 3 _ 4 _ _ _ x _ 7
// _ 4 _ _ _ _ _ x _
// 4 _ 5 _ _ _ 7 _ x
//

uint8_t const rules [9][9] =
{
	/* 0 */ {'x', '_',  1 , '_', '_', '_',  3 , '_',  4 },

	/* 1 */ {'_', 'x', '_', '_', '_', '_', '_',  4 , '_'},

	/* 2 */ { 1 , '_', 'x', '_', '_', '_',  4 , '_',  5 },

	/* 3 */ {'_', '_', '_', 'x', '_',  4 , '_', '_', '_'},

	/* 4 */ {'_', '_', '_', '_', 'x', '_', '_', '_', '_'},

	/* 5 */ {'_', '_', '_',  4 , '_', 'x', '_', '_', '_'},

	/* 6 */ { 3 , '_',  4 , '_', '_', '_', 'x', '_',  7 },

	/* 7 */ {'_',  4 , '_', '_', '_', '_', '_', 'x', '_'},

	/* 8 */ { 4 , '_',  5 , '_', '_', '_',  7 , '_', 'x'},
};

struct Context
{
	static constexpr uint8_t f_on = 1;
	static constexpr uint8_t f_off = 0;

	const uint8_t begin;
	const uint8_t len;

	uint8_t flag[9] = {};
	uint8_t path[9] = {};

	uint8_t cur;

	Context(uint8_t begin, uint8_t len) :
		begin(begin), len(len)
	{
		path[0] = begin;
		flag[begin] = f_on;
		cur = 1;
	}

	void show() const
	{
		cout << endl << "show || cur: " << int(cur) << " | ";
		for (uint8_t i = 0; i < len; ++i) {
			if (i < cur) { cout << static_cast<int>(path[i]) << ", "; }
			else { cout << "_, "; }
		}
		cout << " | ";
		for (uint8_t i = 0; i < 9; ++i) {
			cout << " " << (flag[i] == f_on ? '*' : '-');
		}
		cout << endl;
	}

	void increase()
	{
		for (; inc(0xFF); show()) {}
	}

	bool dec(uint8_t* c)
	{
		if (cur) {
			*c = path[--cur];
			flag[*c] = f_off;
			cout << "dec: " << int(*c) << endl;
			return true;
		}
		else { return false; }
	}

	bool inc(uint8_t const c)
	{
		if (cur < len) {
			for (uint8_t x = c + 1; x < 9; ++x) {
				if (flag[x] == f_off) {
					auto r = rules[path[cur - 1]][x];
					if (r == '_' || flag[r] == f_on) {
						path[cur++] = x;
						flag[x] = f_on;
						return true;
					}
				}
			}
		}
		return false;
	}
};

int count_pattern(uint8_t begin, uint32_t len)
{
	if (begin > 9) { return -1; }

	if (len == 0) { return 0; }
	if (len == 1) { return 1; }
	if (len > 9) { return 0; }

	int result = 0;

	Context ctx(begin, len);
	ctx.show();

	ctx.increase();
	++result;

	uint8_t c;

	cout << "xxxxxxxxxxxx" << endl;

	while (ctx.cur) {
		cout << "~~~~~~~~" << endl;
		while (ctx.dec(&c) && ctx.inc(c)) { ctx.show(); ++result; }
		cout << "^^^^^^^^" << endl;
		while (ctx.dec(&c) && ctx.cur && !ctx.inc(c)) {}
		if (ctx.cur) { ctx.increase(); ++result; }
		cout << "--------" << endl;
	}

	return result;
}

unsigned int countPatternsFrom(char firstDot, unsigned short length) {
	return count_pattern(firstDot - 'A', length);
}

void test()
{
	int result = -1;

	result = count_pattern(2, 2);

	cout << "result: " << result << endl;
}

int main()
{
	test();
	return 0;
}
