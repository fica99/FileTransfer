#include "Socket.h"

Socket::Socket(int domain, int type, int protocol) {
	socket_fd_ = socket(domain, type, protocol);
	if (socket_fd_ == -1)
		ERROR("Failed to get socket file descriptor");
}

int	Socket::getSocketFd(void) const {
	return socket_fd_;
}

void	Socket::setTimeout(time_t seconds, suseconds_t microseconds) const {
	struct timeval tv;
	int	res;

	tv.tv_sec = seconds;
	tv.tv_usec = microseconds;
	res = setsockopt(socket_fd_, SOL_SOCKET, SO_RCVTIMEO,(char *)&tv, sizeof(tv));
	if (res == -1)
		ERROR("Failed to set timeout");
}

void	Socket::closeSocket(void) {
	if (socket_fd_)
		close(socket_fd_);
}

Socket::~Socket() {
	closeSocket();
}

void	Socket::binding(const struct sockaddr *address, socklen_t address_len) {
	int	rv = 1;

	if (setsockopt(socket_fd_, SOL_SOCKET, SO_REUSEADDR, &rv, sizeof(int)) == -1)
		ERROR("Setsockopt failed");
	if (bind(socket_fd_, address, address_len) == -1) {
		closeSocket();
		ERROR("Failed binding socket fd");
	}
}
