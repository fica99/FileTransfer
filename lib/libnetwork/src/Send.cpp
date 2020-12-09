#include "Send.h"

using namespace	std;

size_t	Send::sendall(int fd, const void *msg, size_t len,
					const struct sockaddr *dest_addr, socklen_t dest_len) {
	int			size;

	size = sendto(fd, msg, len, 0, dest_addr, dest_len);
	if (size < 0)
		throw runtime_error("Sendto() error");
	return size;
}

