#ifndef _FLAG_STAFF_
#define _FLAG_STAFF_

namespace flagstaff
{

class Task;

class Engine
{
public:
	Engine() = default;
	virtual ~Engine() = default;

	Engine(const Engine&) = delete;
	Engine& operator= (const Engine&) = delete;

	virtual int run() = 0;
	virtual int addTask(Task*) = 0;
};

Engine* GetEngineInstance();

}

#endif // _FLAG_STAFF_
