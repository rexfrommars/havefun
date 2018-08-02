#include <iostream>
#include <memory>

#include "log.h"
#include "flagstaff.h"
#include "task.h"
#include "epollee.h"
#include "conn.h"
#include "child.h"

using namespace std;

_FS_LOG_

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

void test_child()
{
	_i << "test child!" << endl;
	auto child = flagstaff::Child();
	child.run();

	return;
}

int main()
{
	test_child();
	return 0;

	std::cout << "flagstaff!!" << std::endl;

	flagstaff::SignalHandle::MaskSignals();
	flagstaff::SignalHandle::Install();
	flagstaff::IdleTask::InitIdleTask(10000);
	auto engine = flagstaff::GetEngineInstance();
	return engine->run();
}

