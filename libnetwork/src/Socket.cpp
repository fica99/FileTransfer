#include "Socket.h"

using namespace	std;

Socket::Socket(AddrInfo addr_info) : addr_info_(move(addr_info)) {
	info_ = nullptr;
	createSocket();
}

void	Socket::createSocket(void) {
	if (!info_)
		info_ = addr_info_.getAddrInfo();
	else {
		closeSocket();
		info_ = info_->ai_next;
	}
	while (info_) {
		socket_fd_ = socket(info_->ai_family, info_->ai_socktype,
									info_->ai_protocol);
		if (socket_fd_ != -1)
			break ;
		info_ = info_->ai_next;
	}
	if (!info_)
		Error{"Failed to get socket file descriptor"};

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

void	Socket::closeSocket(void) const {
	close(socket_fd_);
}

Socket::~Socket() {
	closeSocket();
}
