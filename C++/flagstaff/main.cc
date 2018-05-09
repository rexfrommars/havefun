#include "flagstaff.h"
#include "task.h"

#include <iostream>

using namespace std;


void test_chrono()
{
	using namespace flagstaff;
	NoopTask a("a");
	NoopTask b("b");

	a.delay(2000);
	b.delay(4000);

	TaskQueue::push(&a);
	TaskQueue::push(&b);

	Task *t = TaskQueue::top();
	cout << t->name() << endl;

	TaskQueue::pop();
	TaskQueue::pop();
	TaskQueue::pop();
}


int main()
{
	std::cout << "flagstaff!!" << std::endl;

	test_chrono();

	auto engine = flagstaff::GetEngineInstance();
	return engine->run();
}
