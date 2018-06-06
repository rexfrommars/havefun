#include "child.h"

#include "task.h"
#include "flagstaff.h"

using namespace flagstaff;

int Child::launch()
{
	_pid = fork();
	return _pid;
}

int Child::run()
{
	IdleTask::InitIdleTask(4000);
	return GetEngineInstance()->run();
}
