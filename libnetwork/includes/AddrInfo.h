#pragma once

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <sstream>
#include <cstring>
#include "Error.h"

class AddrInfo {
public:
	AddrInfo(const char *ip_addr, const char *serv_port, int socktype);
	AddrInfo(const AddrInfo& other) = delete;
	AddrInfo(AddrInfo&& other);
	AddrInfo& operator=(const AddrInfo& other) = delete;
	AddrInfo& operator=(AddrInfo&& other);
	~AddrInfo(void);
	const struct addrinfo *getAddrInfo() const;
private:
	struct addrinfo	*serv_info_;
};
