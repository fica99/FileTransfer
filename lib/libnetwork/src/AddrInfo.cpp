#include "AddrInfo.h"

using namespace	std;

AddrInfo::AddrInfo(const char *ip_addr,
									const char *serv_port,
									int socktype) : serv_info_(nullptr) {
	int							rv;
	struct addrinfo	hints;

	memset((void*)&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = socktype;
	if (!ip_addr || *ip_addr == '\0')
		hints.ai_flags = AI_PASSIVE;
	rv = getaddrinfo(ip_addr, serv_port, &hints, &serv_info_);
	if (rv != 0)
		ERROR(string("getaddrinfo: ") + gai_strerror(rv));
}

struct addrinfo *AddrInfo::getAddrInfo() {
	return serv_info_;
}

AddrInfo::AddrInfo(AddrInfo&& other) {
	serv_info_ = other.serv_info_;
	other.serv_info_ = nullptr;
}

AddrInfo::~AddrInfo(void) {
	if (!serv_info_)
		return ;
	freeaddrinfo(serv_info_);
	serv_info_ = nullptr;
}
