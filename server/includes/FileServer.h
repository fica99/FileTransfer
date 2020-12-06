#pragma once

#include "AddrInfo.h"
#include "Socket.h"
#include "Bind.h"


class FileServer {
public:
	FileServer(const char *serv_port);
private:
	Socket	sock_;
};
