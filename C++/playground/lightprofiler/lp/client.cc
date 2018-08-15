#include <iostream>

#include <unistd.h>

#include "lpclient.hh"

using namespace std;
using namespace light_profiler;

void run()
{
	process_init();

	while (true) {
		sleep(10);
	}
}

int main()
{
	run();

	return 0;
}
