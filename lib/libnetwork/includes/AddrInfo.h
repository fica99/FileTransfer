#pragma once

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <sstream>
#include <cstring>
#include <string>
#include "Error.h"
#define MAX_PORT_LENGTH 5

class AddrInfo {
public:
	explicit AddrInfo(const char *ip_addr, const char *serv_port, int socktype);
	AddrInfo(const AddrInfo& other) = delete;
	AddrInfo(AddrInfo&& other);
	~AddrInfo(void);
	AddrInfo&	operator=(const AddrInfo& other) = delete;
	AddrInfo&	operator=(AddrInfo&& other);
	const struct addrinfo	*getAddrInfo(void) const;
	void									updateAddrInfo(void);
private:
	void						clearInfo(void);
	void						copyInfo(AddrInfo& other);
	char						ip_addr_[INET6_ADDRSTRLEN + 1];
	char						serv_port_[MAX_PORT_LENGTH + 1];
	int							socktype_;
	struct addrinfo	*serv_info_;
};
