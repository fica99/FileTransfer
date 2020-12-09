#include "Recv.h"

using namespace	std;

size_t	Recv::recvall(int fd, void *buf, size_t len,
															struct sockaddr *from, socklen_t *fromlen) {
	int										size;

	size = recvfrom(fd, buf, len, 0, from, fromlen);
	if (errno == EWOULDBLOCK)
			return 0;
	if (size < 0)
		throw runtime_error("Recvfrom() error");
	return size;
}
