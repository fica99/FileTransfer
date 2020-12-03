#pragma once

#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include "Error.h"
#include "AddrInfo.h"


class Socket {
public:
	Socket(AddrInfo addr_info);
	Socket(Socket&& other);
	Socket(const Socket& other) = delete;
	Socket& 							operator=(Socket&& other);
	Socket& 							operator=(const Socket& other) = delete;
	int										getSocketFd(void) const;
	const struct addrinfo *getSocketInfo(void) const;
	void									createSocket(void);
	~Socket();
private:
	void									closeSocket(void) const;
	AddrInfo							addr_info_;
	int										socket_fd_;
	const struct addrinfo	*info_;
};


