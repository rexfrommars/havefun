#include "task.h"

#include <queue>

#include "log.h"

_FS_LOG_

using namespace flagstaff;
using namespace std;

int IdleTask::InitIdleTask(int interval_ms, const string& name)
{
	auto x = make_shared<IdleTask>(interval_ms, name);
	TaskQ::push(x);

	_i << "init IdleTask:" << name << " with interval:" << interval_ms << endl;
	return 0;
}

Task::ExecuteCode IdleTask::execute()
{
	_i << "This is IDLE task!" << endl;

	return ExecuteCode::REPEAT;
}

namespace {

	class task_cmp
	{
	public:
		bool operator() (const shared_ptr<Task>& a, const shared_ptr<Task>& b)
		{
			return a->next_execute_time() > b->next_execute_time();
		}
	};

	std::priority_queue<shared_ptr<Task>, std::vector<shared_ptr<Task>>, task_cmp> _task_queue;
}

void TaskQ::push(const shared_ptr<Task>& task)
{
	_task_queue.push(task);
}

shared_ptr<Task> TaskQ::top()
{
	return _task_queue.top();
}

void TaskQ::pop()
{
	_task_queue.pop();
}

shared_ptr<Task> TaskQ::safe_top() noexcept
{
	return _task_queue.size() ? _task_queue.top() : shared_ptr<Task>(nullptr);
}

void TaskQ::safe_pop() noexcept
{
	if (_task_queue.size()) {
		_task_queue.pop();
	}
}


