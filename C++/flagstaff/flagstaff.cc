#include <sys/epoll.h>

#include <iostream>
#include "task.h"

// TODO
// eventfd, signalfd, timerfd

using namespace std;

class FlagStaffEngine
{
public:
	static FlagStaffEngine* getInstance();

	int run();

private:
	static FlagStaffEngine* _instance;

	FlagStaffEngine();
	FlagStaffEngine(const FlagStaffEngine&) = delete;
	FlagStaffEngine& operator= (const FlagStaffEngine&) = delete;

	int _epoll_errno;
	int _epollfd;

	// TODO heere TIME-TASK-Q std::priority_queue
};

FlagStaffEngine* FlagStaffEngine::_instance = nullptr;

FlagStaffEngine* FlagStaffEngine::getInstance()
{
	if (_instance == nullptr) {
		_instance = new FlagStaffEngine();
	}

	return _instance;
}

FlagStaffEngine::FlagStaffEngine() : _epoll_errno(0), _epollfd(-1)
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


void test_chrono()
{
	using namespace flagstaff;
	NoopTask a("a");
	NoopTask b("b");

	a.delay(2000);
	b.delay(4000);

	TaskQueue::push(&a);
	TaskQueue::push(&b);

	Task *t = TaskQueue::top();
	cout << t->name() << endl;

	TaskQueue::pop();
	TaskQueue::pop();
	TaskQueue::pop();
}


int main()
{
	std::cout << "flagstaff!!" << std::endl;

	test_chrono();

	auto engine = FlagStaffEngine::getInstance();
	return engine->run();
}
