#pragma once

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <sstream>
#include <cstring>
#include <string>
#include "Error.h"

class AddrInfo {
public:
	AddrInfo(const char *ip_addr, const char *serv_port, int socktype);
	AddrInfo(const AddrInfo& other) = delete;
	AddrInfo(AddrInfo&& other);
	~AddrInfo(void);
	AddrInfo&	operator=(const AddrInfo& other) = delete;
	AddrInfo&	operator=(AddrInfo&& other);
	const struct addrinfo	*getAddrInfo(void) const;
	void									updateAddrInfo(void);
private:
	std::string			ip_addr_;
	std::string			serv_port_;
	int							socktype_;
	struct addrinfo	*serv_info_;
};
