#ifndef _FLAG_STAFF_SELECTABLE_
#define _FLAG_STAFF_SELECTABLE_

namespace flagstaff
{

class Epollee
{
public:
	Epollee() = default;
	virtual ~Epollee() = default;

	int fd() const { return _fd; }
	int events() const { return _events; }

	virtual int onEvent() = 0;
	virtual int onInEvent() = 0;
	virtual int onOutEvent() = 0;

protected:
	int _fd;
	uint64_t _events;
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
