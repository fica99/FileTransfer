#pragma once

#include "AddrInfo.h"
#include "Socket.h"
#include "LogInfo.h"
#include <iostream>


class FileClient {
public:
	FileClient(const char *ip, const char *serv_port);
private:
	Socket	sock_;
};
