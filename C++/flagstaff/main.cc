#include <iostream>
#include <memory>

#include "flagstaff.h"
#include "task.h"
#include "epollee.h"
#include "conn.h"

using namespace std;

void test_chrono()
{
	using namespace flagstaff;
	{
		auto x = make_shared<NoopTask>("noop");
	}

	auto a = make_shared<NoopTask>("a");
	auto b = make_shared<NoopTask>("b");

	a->delay_ms(2000);
	b->delay_ms(4000);

	TaskQ::push(a);
	TaskQ::push(b);

	auto x = TaskQ::top();
	cout << x->name() << endl;
	TaskQ::pop();

	x = TaskQ::top();
	cout << "NoopTask: " << x->name() << endl;
	TaskQ::pop();
}

int main()
{
	std::cout << "flagstaff!!" << std::endl;

	test_chrono();

	flagstaff::IdleTask::InitIdleTask(3000);
	auto engine = flagstaff::GetEngineInstance();
	return engine->run();
}
