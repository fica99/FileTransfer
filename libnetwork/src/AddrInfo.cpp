#include "AddrInfo.h"

using namespace	std;

AddrInfo::AddrInfo(const char *ip_addr, const char *serv_port, int socktype) {
	int				rv;
	struct addrinfo	hints;

	memset((void*)&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = socktype;
	if (!ip_addr)
		hints.ai_flags = AI_PASSIVE;
	rv = getaddrinfo(ip_addr, serv_port, &hints, &serv_info_);
	if (rv != 0) {
		stringstream ss;

		ss << "getaddrinfo: " << gai_strerror(rv);
		throw invalid_argument(ss.str());
	}
}

const struct addrinfo *AddrInfo::getAddrInfo() const {
	return serv_info_;
}

AddrInfo::AddrInfo(AddrInfo&& other) {
	serv_info_ = other.serv_info_;
	other.serv_info_ = nullptr;
}

AddrInfo&	AddrInfo::operator=(AddrInfo&& other) {
	serv_info_ = other.serv_info_;
	other.serv_info_ = nullptr;
	return *this;
}

AddrInfo::~AddrInfo(void) {
	freeaddrinfo(serv_info_);
}
