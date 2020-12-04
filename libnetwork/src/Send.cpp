#include "Send.h"

using namespace	std;

int	Send::sending(const Socket& sock, const char *msg, size_t len) {
	const struct addrinfo	*info = sock.getSocketInfo();
	int										fd = sock.getSocketFd();
	int										sended;
	int										size;

	sended = 0;
	while (sended < len) {
		size = sendto(fd, msg, len, 0, info->ai_addr, info->ai_addrlen);
		if (size < 0)
			throw runtime_error("Sendto() error");
		sended += size;
	}
	return sended;
}

int	Send::sending(const Socket& sock, string msg) {
	return sending(sock, msg.c_str(), msg.size());
}

int	Send::sending(const Socket& sock, const string& msg) {
	return sending(sock, msg.c_str(), msg.size());
}
