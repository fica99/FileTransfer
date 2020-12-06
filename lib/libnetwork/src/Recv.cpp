#include "Recv.h"

using namespace	std;

void	Recv::recving(const Socket& sock, void *buf, size_t len) {
	const struct addrinfo	*info = sock.getSocketInfo();
	int										fd = sock.getSocketFd();
	size_t								got;
	int										size;

	got = 0;
	while (got < len) {
		size = recvfrom(fd, buf, len, 0, info->ai_addr,
									(socklen_t*)&info->ai_addrlen);
		if (size < 0)
			throw runtime_error("Recvfrom() error");
		got += size;
	}
}
