#include "FileClient.h"

using	namespace	std;

FileClient::FileClient(const char *ip, const char *serv_port)
			: sock_(AddrInfo(ip, serv_port, SOCK_DGRAM)) {
	LOG_INFO(1, "Create client to send on: ip - %s port - %s\n", ip, serv_port);
}
