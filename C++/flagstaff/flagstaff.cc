#include "flagstaff.h"

#include <sys/epoll.h>
#include <iostream>

#include "task.h"

// TODO
// eventfd, signalfd, timerfd

using namespace std;
using namespace flagstaff;

namespace {

class FlagStaffEngine : public Engine
{
public:
	int run();
	int addTask(Task* task)
	{
		TaskQueue::push(task);
		return 0;
	}

	FlagStaffEngine();

private:
	FlagStaffEngine(const FlagStaffEngine&) = delete;
	FlagStaffEngine& operator= (const FlagStaffEngine&) = delete;

	int _epoll_errno;
	int _epollfd;

	// TODO heere TIME-TASK-Q std::priority_queue
};

FlagStaffEngine* _engine = nullptr;

}

Engine* flagstaff::GetEngineInstance()
{
	if (_engine == nullptr) {
		_engine = new FlagStaffEngine();
	}
	return _engine;
}

FlagStaffEngine::FlagStaffEngine() : Engine(), _epoll_errno(0), _epollfd(-1)
{
	_epollfd = epoll_create1(EPOLL_CLOEXEC);
	_epoll_errno = errno;
}

int FlagStaffEngine::run()
{
	// TODO

	for (int i = 5; i; --i) {
		epoll_event event;

		int num = epoll_wait(_epollfd, &event, 1, 2000);
		cout << "wake up ... " << num << " | " << errno << endl;

		if (num > 0) {
			// TODO
		}
		else if (num == 0) {
			// timeout
		}
		else { // -1
			auto _errno = errno;
			switch (_errno)
			{
			case EINTR:
				break;
			// EBADF
			// EFAULT
			// EINVAL

			default:
				break;
			}
		}
	}

	return 0;
}

