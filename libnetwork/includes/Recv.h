#pragma once

#include <sys/socket.h>
#include <stdexcept>
#include "Socket.h"


class Recv {
public:
	static void	recving(const Socket& sock, void *buf, size_t len);
};
