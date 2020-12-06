#include "FileServer.h"

FileServer::FileServer(const char *serv_port)
								: sock_(AddrInfo(NULL, serv_port, SOCK_DGRAM)) {
	Bind::binding(sock_);
}
