#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

struct E
{
	char c;
	int cc;

	E(char _c, int _cc) : c(_c), cc(_cc) {}
};

using len_t = string::size_type;

void _p(vector<E> x, vector<string>& results, char* b, const len_t cur, const len_t l)
{
	if (cur == l) {
		results.push_back(b);
		return;
	}

	for (size_t i = 0; i < x.size(); ++i) {
		if (x[i].cc) {
			b[cur] = x[i].c;
			--x[i].cc;
			_p(x, results, b, cur + 1, l);
			++x[i].cc;
		}
	}
}

vector<string> permutations(const string& _s)
{
	const len_t len = _s.length();

	vector<char> vc(len + 1);
	char* s = vc.data();

	memcpy(s, _s.data(), len);
	std::sort(s, s + len);

	vector<E> x;
	char c = s[0];
	char cc = 1;
	for (size_t i = 1; i < len; ++i) {
		if (s[i] == c) {
			++cc;
		}
		else {
			x.emplace_back(c, cc);
			c = s[i];
			cc = 1;
		}
	}
	if (c) {
		x.emplace_back(c, cc);
	}

	vector<string> results;
	_p(x, results, s, 0, len);
	return results;
}


void test(const string& str)
{
	vector<string> r = permutations(str);

	for (const auto& s: r) {
		cout << " -- " << s << endl;
	}
}

int main()
{
	test("aab");
}

