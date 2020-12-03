#pragma once

#include "AddrInfo.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <stdexcept>
#include <unistd.h>

class Socket {
public:
	Socket(AddrInfo addr_info);
	Socket(Socket&& other);
	Socket(const Socket& other) = delete;
	Socket& 							operator=(Socket&& other);
	Socket& 							operator=(const Socket& other) = delete;
	int										getSocketFd(void) const;
	const struct addrinfo *getSocketInfo(void) const;
	~Socket();
private:
	AddrInfo							addr_info_;
	int										socket_fd_;
	const struct addrinfo	*info_;
};


