#include "epollee.h"

#include <signal.h>
#include <sys/signalfd.h>
#include <unistd.h>

#include <cstring>

#include "log.h"
#include "flagstaff.h"

using namespace std;
using namespace flagstaff;

_FS_LOG_

Epollee::~Epollee() = default;

int Epollee::onEvent(uint64_t events)
{
	int rc = 0;
	if (events & EPOLLIN) {
		rc = onInEvent();
	}
	if (events & EPOLLOUT) {
		rc = onOutEvent();
	}
	if (events & EPOLLHUP) {
		rc = onHupEvent();
	}
	if (events & EPOLLERR) {
		rc = onErrEvent();
	}

	return rc;
}

namespace {

int signal_fd = -1;
sigset_t signal_mask;

}

int SignalHandle::MaskSignals()
{
	int rc = sigprocmask(SIG_SETMASK, nullptr, &signal_mask);

	sigaddset(&signal_mask, SIGTERM);
	sigaddset(&signal_mask, SIGINT);

	rc = sigprocmask(SIG_SETMASK, &signal_mask, nullptr);
	_i << "mask signals got: " << rc << endl;
	return rc;
}

int SignalHandle::Install()
{
	if (signal_fd == -1) {
		signal_fd = signalfd(signal_fd, &signal_mask, SFD_NONBLOCK | SFD_CLOEXEC);
		SignalHandle* handle = new SignalHandle(signal_fd);
		int rc = flagstaff::GetEngineInstance()->add_target(handle);
		if (rc) {
			_e << "install signal hadle failed!" << endl;
		}
		return rc;
	}
	return 0;
}

int SignalHandle::onInEvent()
{
	signalfd_siginfo ssi;
	while (true) {
		ssize_t len = read(_fd, &ssi, sizeof(ssi));
		if (len == sizeof(ssi)) {
			// TODO
			_i << ssi.ssi_signo << endl;
			_i << ssi.ssi_errno << endl;
			_i << ssi.ssi_code << endl;
			_i << ssi.ssi_pid << endl;
			_i << ssi.ssi_uid << endl;

			switch (ssi.ssi_signo)
			{
			case SIGTERM:
				_w << "Got SIGTERM" << endl;
				flagstaff::GetEngineInstance()->stop();
				break;

			case SIGINT:
				_w << "Got SIGINT" << endl;
				flagstaff::GetEngineInstance()->stop();
				break;

			// TODO other signals
			default:
				break;
			}

			continue;
		}
		else if (len == -1) {
			int _errno = errno;
			// TODO
			if (_errno == EAGAIN || _errno == EWOULDBLOCK) {
				return 0;
			}
			else {
				// TODO
				_e << "read from signal_fd got error: " << strerror(_errno) << " (" << _errno << ")" << endl;
				return -1;
			}
		}
		else {
			_e << "read from signal_fd got impossible len: " << len << endl;
			return -1;
		}
	}
}

