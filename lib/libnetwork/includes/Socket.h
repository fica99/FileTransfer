#pragma once

#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <cstring>
#include "Error.h"

class Socket {
public:
	Socket(int domain, int type, int protocol);
	~Socket();
	int										getSocketFd(void) const;
	void									closeSocket(void);
	void									binding(const struct sockaddr *address, socklen_t address_len);
	void									setTimeout(time_t seconds,
															suseconds_t microseconds) const;
private:
	int										socket_fd_;
};


