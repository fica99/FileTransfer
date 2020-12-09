#pragma once

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/errno.h>
#include <stdexcept>


class Recv {
public:
	static size_t	recvall(int fd, void *buf, size_t len,
					struct sockaddr *from, socklen_t *fromlen);
};
