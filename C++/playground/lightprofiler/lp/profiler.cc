#include <iostream>
#include <sstream>

#include <unistd.h>
#include <signal.h>

#include <sys/types.h>
#include <sys/syscall.h>
#include <sys/socket.h>
#include <sys/un.h>

#include "lpcommon.hh"

namespace {

int init_sock(const std::string& path)
{
	int errno_;
	int rc;

	int sock = socket(AF_UNIX, SOCK_DGRAM, 0);
	if (sock == -1) {
		errno_ = errno;
		std::cerr << __LINE__ << strerror(errno_) << std::endl;
		return -1;
	}

	sockaddr_un addr;
	addr.sun_family = AF_UNIX;
	strncpy(addr.sun_path, path.c_str(), std::size(addr.sun_path));

	rc = bind(sock, reinterpret_cast<sockaddr*>(&addr), sizeof(addr));
	if (rc) {
		errno_ = errno;
		std::cerr << __LINE__ << strerror(errno_) << std::endl;
		return -1;
	}

	return sock;
}

int run(const char* client_pid)
{
	int pid = atoi(client_pid);

	if (pid == 0) {
		std::cerr << "Invalid client pid! " << client_pid << std::endl;
		return -1;
	}

	std::ostringstream oss;
	oss << light_profiler::LP_SOCK_PREFIX << client_pid;
	std::string path = oss.str();

	std::cout << path << std::endl;

	int sock = init_sock(path);

	char buff[4096];

	while (true) {
		sleep(2);

		kill(pid, SIGPROF);

		ssize_t received = recv(sock, buff, sizeof(buff), 0);
		std::cout << "received: " << received << std::endl;
	}

	unlink(path.c_str());

	return 0;
}

} // anonymous namespace

int main(int argc, char** argv)
{
	std::cout << argc << std::endl;
	std::cout << argv[0] << std::endl;

	if (argc != 2) {
		std::cerr << "Usage: " << argv[0] << " client_pid" << std::endl;
		return 0;
	}

	run(argv[1]);

	return 0;
}
