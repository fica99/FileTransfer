#pragma once

#include "Socket.h"
#include <cstring>
#include <stdexcept>

class Send {
public:
	static int sending(const Socket& sock, const char *msg, size_t len);
	static int sending(const Socket& sock, const string& msg);
	static int sending(const Socket& sock, string msg);
};
