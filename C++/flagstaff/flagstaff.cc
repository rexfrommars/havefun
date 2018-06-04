#include "flagstaff.h"

#include <sys/epoll.h>
#include <iostream>

#include "log.h"
#include "task.h"

// TODO
// eventfd, signalfd, timerfd

using namespace std;
using namespace flagstaff;

_FS_LOG_

namespace {

class FlagStaffEngine : public Engine
{
public:
	int add_target(Epollee* target) override
	{
		_i << "to add target to engine: " << target->name() << endl;
		int rc = _ctl(EPOLL_CTL_ADD, target->fd(), target->events(), target);
		if (rc) {
			// TODO
			_i << rc << endl;
		}
		return rc;
	}

	int del_target(Epollee* target) override
	{
		_i << "to del target from engine: " << target->name() << endl;
		int rc = _ctl(EPOLL_CTL_DEL, target->fd(), target->events(), target);
		if (rc) {
			// TODO
		}
		return rc;
	}

	int run() override;
	int stop() override { _running = false; return 0; }

	FlagStaffEngine();

private:
	// TODO
	// super class has set these two function "delete"
	// do we need to do it again?
	FlagStaffEngine(const FlagStaffEngine&) = delete;
	FlagStaffEngine& operator= (const FlagStaffEngine&) = delete;

	int _epoll_errno;
	int _epollfd;
	bool _running;

	int _ctl(int op, int fd, uint64_t events, Epollee* target)
	{
		epoll_event event;
		event.events = events;
		event.data.ptr = target;

		int rc = epoll_ctl(_epollfd, op, fd, &event);
		return rc;
	}
};

FlagStaffEngine* _engine = nullptr;

} // namespace

Engine* flagstaff::GetEngineInstance()
{
	if (_engine == nullptr) {
		_engine = new FlagStaffEngine();
	}
	return _engine;
}

FlagStaffEngine::FlagStaffEngine() : Engine(), _epoll_errno(0), _epollfd(-1), _running(true)
{
	_epollfd = epoll_create1(EPOLL_CLOEXEC);
	_epoll_errno = errno;
}

int FlagStaffEngine::run()
{
	// TODO

	int wait_ms = -1;
	while (_running) {
		auto task = TaskQ::safe_top();
		if (task) {
			_i << task->name() << " | " << task->wait_time_ms() << endl;
			wait_ms = task->wait_time_ms();
		}
		else {
			wait_ms = -1;
		}

		epoll_event event;

		_i << "wait time: " << wait_ms << endl;
		int num = epoll_wait(_epollfd, &event, 1, wait_ms);

		cout << "wake up ... " << num << " | " << errno << endl;

		if (num > 0) {
			Epollee* epollee = reinterpret_cast<Epollee*>(event.data.ptr);
			epollee->onEvent(event.events);
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

		task = TaskQ::safe_top();
		if (task && task->wait_time_ms() < 1) {
			TaskQ::pop();
			Task::ExecuteCode code = task->execute();
			_i << "execute code: " << code << endl;
			switch (code)
			{
			case Task::ExecuteCode::OK:
				break;
			case Task::ExecuteCode::REPEAT:
				task->reset();
				TaskQ::push(task);
				break;
			}
		}
	}

	return 0;
}

