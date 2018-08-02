#include <string>
#include <iostream>

int main()
{
	std::string s = "";
	auto capa = 0;

	for (int i = 0; i < 100; ++i) {
		s += "aaaabbbbccccddddeeeeffff";

		if (capa != s.capacity()) {
			std::cout << capa << " --> " << s.capacity() << std::endl;
			capa = s.capacity();
		}
	}

	// std::cout << s << std::endl;

	return 0;
}
