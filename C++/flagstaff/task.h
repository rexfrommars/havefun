#ifndef _FLAGSTAFF_TASK_
#define _FLAGSTAFF_TASK_

#include <chrono>
#include <string>
#include <memory>
#include <iostream>

namespace flagstaff {

class Task // TODO: different types of tasks: onshot, repeatable, periodically
{
public:
	using clock = std::chrono::steady_clock;

	explicit Task(const std::string& name) :
		_name(name), _repeatable(false), _interval_ms(0), _interval(0),
		_last_execute_time(clock::duration(0)), _next_execute_time(clock::now())
	{}

	Task(const std::string& name, int interval_ms) :
		_name(name), _repeatable(true), _interval_ms(interval_ms),
		_interval(std::chrono::duration_cast<clock::duration>(std::chrono::milliseconds(interval_ms))),
		_last_execute_time(clock::duration(0)), _next_execute_time(clock::now())
	{}

	virtual ~Task() = default;

	const std::string& name() const {return _name; }
	bool repeatable() const { return _repeatable; }

	void set_interval_ms(int interval_ms)
	{
		_repeatable = true;
		_interval_ms = interval_ms;
		_interval = std::chrono::duration_cast<clock::duration>(std::chrono::milliseconds(interval_ms));
	}

	void delay_ms(int ms)
	{
		_next_execute_time = clock::now() + std::chrono::milliseconds(ms);
	}

	void reset()
	{
		_next_execute_time = clock::now() + _interval;
	}

	clock::time_point next_execute_time() const
	{
		return _next_execute_time;
	}

	int wait_time_ms() const
	{
		return std::chrono::duration_cast<std::chrono::milliseconds>(_next_execute_time - clock::now()).count();
	}

	enum ExecuteCode
	{
		OK		= 0,
		REPEAT	= 1,
	};

	virtual ExecuteCode execute() = 0;

private:
	std::string _name;
	bool _repeatable;
	// TODO bool _periodical

	int _interval_ms;
	clock::duration _interval;

	// TODO time_point _init_time
	clock::time_point _last_execute_time;
	clock::time_point _next_execute_time;
};

class NoopTask: public Task
{
public:
	explicit NoopTask(const std::string& name): Task(name) {}

	ExecuteCode execute() override
	{
		return ExecuteCode::OK;
	}
};

class IdleTask: public Task
{
public:
	constexpr static const char * const DEFAULT_NAME = "idle-task";
	static int InitIdleTask(int interval_ms, const std::string& name = DEFAULT_NAME);

	explicit IdleTask(int interval_ms, const std::string& name = DEFAULT_NAME) :
		Task(name, interval_ms)
	{}

	ExecuteCode execute() override;
};

struct TaskQ
{
	static void push(std::shared_ptr<Task> const &);

	static std::shared_ptr<Task> top();
	static void pop();

	static std::shared_ptr<Task> safe_top() noexcept;
	static void safe_pop() noexcept;

	TaskQ() = delete;
};

}

#endif // _FLAGSTAFF_TASK_
