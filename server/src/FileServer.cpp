#include "FileServer.h"

using namespace	std;

FileServer::FileServer(const char *serv_port)//, size_t datagram_size)
								: //datagram_size_(datagram_size),
								sock_(AddrInfo(NULL, serv_port, SOCK_DGRAM)) {
	Bind::binding(sock_);
}



//Datagram	FileServer::getDatagram(void) const {
//	byte	data[datagram_size_ + 1];

//	Recv::recving(sock_, data, datagram_size_);
//	data[datagram_size_] = static_cast<byte>(0);
//}
