#ifndef _FLAG_STAFF_LOG_
#define _FLAG_STAFF_LOG_

#include <iostream>

namespace flagstaff
{

class Log
{
public:
	// TODO
};

#define _FS_LOG_ \
	namespace { \
		using std::endl; \
		auto& _i = std::cout; \
		auto& _e = std::cerr; \
	} \

}

#endif // _FLAG_STAFF_LOG_
