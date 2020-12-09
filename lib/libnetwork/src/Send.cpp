#include "Send.h"

using namespace	std;

size_t	Send::sending(Socket& sock, const void *msg, size_t len) {
	struct addrinfo	*info = sock.getAddrInfo();
	int										fd = sock.getSocketFd();
	size_t								sended;
	int										size;

	sended = 0;
	while (sended < len) {
		size = sendto(fd, msg, len - sended, 0, info->ai_addr, info->ai_addrlen);
		if (size < 0)
			throw runtime_error("Sendto() error");
		if (!size)
			break ;
		sended += size;
	}
	return sended;
}

