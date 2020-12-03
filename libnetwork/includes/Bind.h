#pragma once

#include <sys/types.h>
#include <sys/socket.h>
#include "Error.h"
#include "Socket.h"

class Bind {
public:
	Bind(Socket& sock);
};
