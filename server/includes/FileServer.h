#pragma once

#include <cstddef>
#include "AddrInfo.h"
#include "Socket.h"
#include "Bind.h"

class FileServer {
public:
	FileServer(const char *serv_port);
	//Datagram	getDatagram(void) const;
private:
	//size_t	datagram_size_;
	Socket	sock_;
};
