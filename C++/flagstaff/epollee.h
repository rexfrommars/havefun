#ifndef _FLAG_STAFF_SELECTABLE_
#define _FLAG_STAFF_SELECTABLE_

#include <sys/epoll.h>

#include <cstdint>
#include <string>

namespace flagstaff
{

class Epollee
{
public:
	Epollee(const std::string& name, int fd, int events) : _name(name), _fd(fd), _events(events)
	{}

	virtual ~Epollee() = 0;

	const std::string& name() const { return _name; }
	int fd() const { return _fd; }
	uint64_t events() const { return _events; }

	virtual int onEvent(uint64_t events);

	virtual int onInEvent() { return 0; }
	virtual int onOutEvent() { return 0; }
	virtual int onHupEvent() { return 0; }
	virtual int onErrEvent() { return 0; }

protected:
	std::string _name;
	int _fd;
	uint64_t _events;
};

class SignalHandle : public Epollee
{
public:
	static int MaskSignals();
	static int Install();

	int onInEvent();

private:
	SignalHandle(int fd) : Epollee("SingalHandle", fd, EPOLLIN)
	{}
};

class Listener : public Epollee
{
public:
	Listener();
	virtual ~Listener() override;

	int fd() { return _fd; }
	int epoll_events() { return _events; }

	int onInEvent() override;

protected:
	int _fd;
	int _events;
};

}

#endif // _FLAG_STAFF_SELECTABLE_
