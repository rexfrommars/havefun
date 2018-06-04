#ifndef _FLAG_STAFF_CONN_
#define _FLAG_STAFF_CONN_

#include <string>

#include "epollee.h"

namespace flagstaff
{

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
