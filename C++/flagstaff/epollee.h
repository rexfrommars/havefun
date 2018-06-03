#ifndef _FLAG_STAFF_SELECTABLE_
#define _FLAG_STAFF_SELECTABLE_

namespace flagstaff
{

class Epollee
{
public:
	Epollee() = default;
	virtual ~Epollee() = default;

	virtual int fd() = 0;
	virtual int epoll_events() = 0;

	virtual int onInEvent() = 0;
	virtual int onOutEvent() = 0;
};

}

#endif // _FLAG_STAFF_SELECTABLE_
