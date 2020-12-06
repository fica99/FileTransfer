#pragma once

#include "Socket.h"
#include <cstring>
#include <stdexcept>

class Send {
public:
	static size_t sending(const Socket& sock, const void *msg, size_t len);
};
