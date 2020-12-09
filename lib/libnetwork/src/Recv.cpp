#include "Recv.h"

using namespace	std;

size_t	Recv::recving(Socket& sock, void *buf, size_t len) {
	struct addrinfo	*info = sock.getAddrInfo();
	int										fd = sock.getSocketFd();
	size_t								got;
	int										size;

	got = 0;
	while (got < len) {
		size = recvfrom(fd, buf, len - got, 0, info->ai_addr, &info->ai_addrlen);
		if (errno == EWOULDBLOCK)
			break;
		if (size < 0)
			throw runtime_error("Recvfrom() error");
		if (!size)
			break ;
		got += size;
	}
	return got;
}
