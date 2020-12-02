#pragma once

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdexcept>
#include <sstream>
#include <cstring>

class AddrInfo {
public:
	AddrInfo(const char *ip_addr, const char *serv_port, int socktype);
	~AddrInfo(void);
	const struct addrinfo *getAddrInfo() const;
private:
	struct addrinfo	*serv_info_;
};
