#pragma once

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdexcept>
#include <sstream>
#include <cstring>

class AddrInfoGetter {
public:
	AddrInfoGetter(const char *ip_addr, const char *serv_port, int socktype);
	~AddrInfoGetter(void);
private:
	struct addrinfo	*serv_info_;
};
