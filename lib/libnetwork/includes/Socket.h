#pragma once

#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include "Error.h"
#include "AddrInfo.h"


class Socket {
public:
	explicit Socket(AddrInfo addr_info);
	~Socket();
	int										updateSocket(void);
	int										getSocketFd(void) const;
	struct addrinfo 			*getAddrInfo(void);
	void									closeSocket(void);
	void									setTimeout(time_t seconds,
															suseconds_t microseconds) const;
private:
	AddrInfo							addr_info_;
	int										socket_fd_;
	struct addrinfo				*info_;
};


