#pragma once

#include <sys/types.h>
#include <sys/socket.h>
#include <stdexcept>

class Send {
public:
	static size_t	sendall(int fd, const void *msg, size_t len,
					const struct sockaddr *dest_addr, socklen_t dest_len);
};
