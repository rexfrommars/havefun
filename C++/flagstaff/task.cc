#include "task.h"

#include <queue>

using namespace flagstaff;
using namespace std;

Task::Task(const string& name) : _name(name), _execute_time(Task::clock::now())
{}

void Task::delay(int ms)
{
	chrono::duration<int, std::milli> duration_ms(ms);
	_execute_time = clock::now() + duration_ms;
}

void Task::pushToQueue()
{
	TaskQueue::push(this);
}

namespace {

	class task_cmp
	{
	public:
		bool operator() (const Task* a, const Task* b)
		{
			return a->execute_time() > b->execute_time();
		}
	};

	std::priority_queue<Task*, std::vector<Task*>, task_cmp> _task_queue;
}


void TaskQueue::push(Task* task)
{
	_task_queue.push(task);
}

void TaskQueue::pop()
{
	_task_queue.pop();
}

Task* TaskQueue::top()
{
	return _task_queue.top();
}

ListenerTask::ListenerTask(const string& name, const string& path) : Task(name), _path(path)
{}

int ListenerTask::execute()
{
	// TODO
	return 0;
}


