#include "AddrInfo.h"

using namespace	std;

AddrInfo::AddrInfo(const char *ip_addr,
									const char *serv_port,
									int socktype) : ip_addr_(ip_addr),
									serv_port_(serv_port), socktype_(socktype),
									serv_info_(nullptr) {
	updateAddrInfo();
}

void							AddrInfo::updateAddrInfo(void) {
	int							rv;
	struct addrinfo	hints;

	memset((void*)&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = socktype_;
	if (ip_addr_.empty())
		hints.ai_flags = AI_PASSIVE;
	rv = getaddrinfo(ip_addr_.c_str(),
			serv_port_.c_str(), &hints, &serv_info_);
	if (rv != 0)
		ERROR(string("getaddrinfo: ") + gai_strerror(rv));
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
	if (serv_info_)
		freeaddrinfo(serv_info_);
}
