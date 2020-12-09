#include "server.h"

using namespace	std;

void			sendDatagram(Socket& sock, Datagram datagram) {
	try {
		size_t nb_sended_bytes = datagram.send(sock);
		LOG_INFO(1, "Server: Send %ld bytes, datagram of size %ld\n", nb_sended_bytes, datagram.getContentSize());
	} catch (exception& ex) {
		cerr << ex.what() << endl;
	}
}
