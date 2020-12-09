#pragma once

#include <sys/socket.h>
#include <stdexcept>
#include "Socket.h"


class Recv {
public:
	static size_t	recving(Socket& sock, void *buf, size_t len);
};
