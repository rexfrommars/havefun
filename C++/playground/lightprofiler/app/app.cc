#include <iostream>
#include <thread>

#include <unistd.h>

// TODO pthread_join on signal?

void func_a()
{
	while (true) {
		auto left = sleep(10);
		(void)left;
	}
}

void func_b()
{

}

void run()
{
	std::thread ta(func_a);

	ta.join();
}

int main()
{
	run();

	return 0;
}
