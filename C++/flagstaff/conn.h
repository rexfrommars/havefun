#ifndef _FLAG_STAFF_CONN_
#define _FLAG_STAFF_CONN_

#include <string>

#include "epollee.h"

namespace flagstaff
{

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

class FileSocketListener : public Listener
{
public:
	explicit FileSocketListener(const std::string& path);
	virtual ~FileSocketListener() override;
};

class TCPListener : public Listener
{
public:
	// TODO
};

}

#endif // _FLAG_STAFF_CONN_
