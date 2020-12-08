#include "Socket.h"

using namespace	std;

Socket::Socket(AddrInfo addr_info) : addr_info_(move(addr_info)),
																		socket_fd_(0),
																		info_(nullptr) {
	updateSocket();
}

int	Socket::updateSocket(void) {
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
		ERROR("Failed to get socket file descriptor");
	return socket_fd_;
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
	if (res == 1)
		ERROR("Failed to set timeout");
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

void	Socket::closeSocket(void) {
	if (socket_fd_)
		close(socket_fd_);
}

Socket::~Socket() {
	closeSocket();
}
