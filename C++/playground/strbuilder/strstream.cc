#include <string>
#include <iostream>
#include <sstream>

int main()
{
	std::stringstream ss;
	for (int i = 0; i < 1000; ++i) {
		ss << "aaaabbbbccccddddeeeeffff";
	}

	std::cout << ss.str() << std::endl;
	return 0;
}
