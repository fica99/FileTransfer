#include "Socket.h"

using namespace	std;

Socket::Socket(AddrInfo addr_info) : addr_info_(move(addr_info)) {
	const struct addrinfo	*p;
	int										socket_fd;

	p = addr_info_.getAddrInfo();
	while (p) {
		socket_fd = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
		if (socket_fd != -1)
			break ;
		p = p->ai_next;
	}
	if (!p)
		throw invalid_argument("Failed to get socket file descriptor");
	info_ = p;
	socket_fd_ = socket_fd;
}

int	Socket::getSocketFd(void) const {
	return socket_fd_;
}

const struct addrinfo *Socket::getSocketInfo(void) const {
	return info_;
}

Socket::Socket(Socket&& other) : addr_info_ (move(other.addr_info_)),
																socket_fd_(other.socket_fd_),
																info_(move(other.info_)) {
	other.info_ = nullptr;
}

Socket& Socket::operator=(Socket&& other) {
	if (&other == this)
			return *this;
	addr_info_ = move(other.addr_info_);
	socket_fd_ = other.socket_fd_;
	info_ = move(other.info_);
	other.info_ = nullptr;
	return *this;
}

Socket::~Socket() {
	close(socket_fd_);
}
