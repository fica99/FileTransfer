#pragma once

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
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
	const struct addrinfo	*getAddrInfo(void) const;
private:
	struct addrinfo	*serv_info_;
};
