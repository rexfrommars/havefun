#ifndef _FLAGSTAFF_TASK_
#define _FLAGSTAFF_TASK_

#include <chrono>
#include <string>

namespace flagstaff {

class Task
{
public:
	typedef std::chrono::steady_clock clock;
	typedef clock::duration duration;
	typedef clock::time_point time_point;

	explicit Task(const std::string& name);
	virtual ~Task() {};

	const std::string& name() const {return _name; }
	const time_point& execute_time() const { return _execute_time; }

	void delay(int ms);
	void pushToQueue();

	virtual int execute() = 0;

private:
	std::string _name;
	time_point _execute_time;
};

class NoopTask: public Task
{
public:
	explicit NoopTask(const std::string& name): Task(name) {}

	int execute() override
	{
		return 0;
	}
};

class TaskQueue
{
public:
	static void push(Task*);
	static Task* top();
	static void pop();


private:
	TaskQueue() = delete;
};

class ListenerTask : public Task
{
public:
	ListenerTask(const std::string& name, const std::string& path);

	int execute() override;

private:
	std::string _path;
};

}

#endif // _FLAGSTAFF_TASK_
