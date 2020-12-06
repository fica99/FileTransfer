#include "AddrInfo.h"

using namespace	std;

AddrInfo::AddrInfo(const char *ip_addr,
									const char *serv_port,
									int socktype) : socktype_(socktype),
									serv_info_(nullptr) {
	if (ip_addr)
		memcpy(ip_addr_, ip_addr, INET6_ADDRSTRLEN);
	else
		*ip_addr_ = '\0';
	if (serv_port)
		memcpy(serv_port_, serv_port, MAX_PORT_LENGTH);
	else
		*serv_port_ = '\0';
	updateAddrInfo();
}

void							AddrInfo::updateAddrInfo(void) {
	int							rv;
	struct addrinfo	hints;

	if (serv_info_)
		clearInfo();
	memset((void*)&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = socktype_;
	if (*ip_addr_ == '\0')
		hints.ai_flags = AI_PASSIVE;
	rv = getaddrinfo(ip_addr_, serv_port_, &hints, &serv_info_);
	if (rv != 0)
		ERROR(string("getaddrinfo: ") + gai_strerror(rv));
}

void							AddrInfo::clearInfo(void) {
	if (!serv_info_)
		return ;
	freeaddrinfo(serv_info_);
	serv_info_ = nullptr;
}

const struct addrinfo *AddrInfo::getAddrInfo() const {
	return serv_info_;
}

AddrInfo::AddrInfo(AddrInfo&& other) {
	copyInfo(other);
}

void	AddrInfo::copyInfo(AddrInfo& other) {
	memcpy(ip_addr_, other.ip_addr_, INET6_ADDRSTRLEN);
	memcpy(serv_port_, other.serv_port_, MAX_PORT_LENGTH);
	socktype_ = other.socktype_;
	serv_info_ = other.serv_info_;
	other.serv_info_ = nullptr;
}

AddrInfo&	AddrInfo::operator=(AddrInfo&& other) {
	if (this == &other)
		return *this;
	copyInfo(other);
	return *this;
}

AddrInfo::~AddrInfo(void) {
	clearInfo();
}
