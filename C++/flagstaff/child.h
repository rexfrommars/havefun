#ifndef _FLAG_STAFF_CHILD_
#define _FLAG_STAFF_CHILD_

#include <unistd.h>

namespace flagstaff
{

class Child
{
public:
	Child() : _pid(-2) {}
	~Child() = default;
	Child(const Child&) = delete;
	Child& operator= (const Child&) = delete;
	Child(Child&&) = delete;
	Child& operator= (Child&&) = delete;

	pid_t launch();
	pid_t pid() const { return _pid; }
	bool is_child() const { return _pid > 0; }
	bool is_parent() const { return _pid == 0; }
	bool error() const { return _pid == -1; }

	int run();

private:
	pid_t _pid;
};

}

#endif // _FLAG_STAFF_CHILD_
