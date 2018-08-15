#include "lpcommon.hh"
#include "lpclient.hh"

#include <iostream>
#include <iterator>
#include <sstream>

#include <signal.h>
#include <execinfo.h>
#include <unistd.h>

#include <sys/syscall.h>
#include <sys/socket.h>
#include <sys/un.h>

namespace {

inline pid_t _gettid()
{
	return syscall(SYS_gettid);
}

thread_local static light_profiler::ProfSample _prof_sample;
thread_local int _sock;

int _init_sock()
{
	int errno_ = 0;
	int rc = 0;

	int sock = socket(AF_UNIX, SOCK_DGRAM, 0);
	if (sock == -1) {
		errno_ = errno;
		std::cerr << __LINE__ << strerror(errno_) << std::endl;
		return -1;
	}

	std::ostringstream oss;
	oss << light_profiler::LP_SOCK_PREFIX << _gettid();
	std::string path = oss.str();

	std::cout << path << std::endl;

	sockaddr_un remote;
	remote.sun_family = AF_UNIX;
	strncpy(remote.sun_path, path.c_str(), std::size(remote.sun_path));

	rc = connect(sock, reinterpret_cast<sockaddr*>(&remote), sizeof(remote));
	if (rc) {
		errno_ = errno;
		std::cerr << __LINE__ << strerror(errno_) << std::endl;
		return -1;
	}

	std::cout << "sock: " << sock << std::endl;

	return sock;
}

int _lp_thread_init()
{
	if ((_sock = _init_sock()) > 0) {
		_prof_sample.thread_id = _gettid();
		_prof_sample.sample_id = 0;
		return 0;
	}
	else {
		return -1;
	}
}

void _bt()
{
	if (_prof_sample.thread_id) {
		_prof_sample.sample_id++;
		_prof_sample.list_size = backtrace(
			reinterpret_cast<void**>(&_prof_sample.addr_list[0]),
			std::size(_prof_sample.addr_list));

		errno = 0;
		ssize_t sent = send(_sock, &_prof_sample, sizeof(_prof_sample), MSG_DONTWAIT);

		std::cout << "sent: " << sent << " | " << strerror(errno) << " | " <<  _prof_sample.sample_id << std::endl;
	}
	else if (!_lp_thread_init()) {
		_bt();
	}
}

void _on_sig(int sig)
{
	std::cout << __func__ << std::endl;
	_bt();
}

} // anonymous namespace

namespace light_profiler {

int process_init()
{
	if (getpid() != _gettid()) {
		std::cerr << __func__ << " is being invoked outside of the main thead!" << std::endl;
		return -1;
	}

	struct sigaction sa;
	sa.sa_handler = _on_sig;

	sigaction(SIGPROF, &sa, nullptr);

	return 0;
}


} // namespace light_profiler
