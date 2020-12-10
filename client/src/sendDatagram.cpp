#include "client.h"

using namespace	std;

void	sendDatagram(const Socket& sock, const AddrInfo& info, const Datagram& datagram) {
	try {
		size_t nb_sended_bytes = sendDatagram(sock.getSocketFd(), datagram,
					info.getAddrInfo()->ai_addr, info.getAddrInfo()->ai_addrlen);
		LOG_INFO(1, "Client: Send %ld bytes\n", nb_sended_bytes);
	} catch (exception& ex) {
		cerr << ex.what() << endl;
	}
}
