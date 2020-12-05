#pragma once

#include "Socket.h"
#include <cstring>
#include <stdexcept>
#include "IDatagram.h"

class Send {
public:
	static size_t sending(const Socket& sock, const void *msg, size_t len);
	static size_t sending(const Socket& sock, const IDatagram& datagram);
};
