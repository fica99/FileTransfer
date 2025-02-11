#include "server.h"

using namespace	std;

void			sendDatagram(int fd, struct sockaddr *from, socklen_t *from_len,
						const Datagram& datagram) {
	try {
		size_t nb_sended_bytes = sendDatagram(fd, datagram, from, *from_len);
		LOG_INFO(1, "Server: Send %ld bytes, datagram of size %ld\n", nb_sended_bytes, datagram.getDatagramSize());
	} catch (exception& ex) {
		cerr << ex.what() << endl;
	}
}
