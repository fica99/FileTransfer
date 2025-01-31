#include "server.h"

using namespace	std;

Datagram	getDatagram(int fd, struct sockaddr *from,
														socklen_t *from_len) {
	Datagram datagram(DATAGRAM_SIZE);

	try {
		size_t got_bytes = recvDatagram(fd, datagram, from, from_len);
		LOG_INFO(1, "Server: Got %ld bytes\n", got_bytes);
		if (!got_bytes) {
			LOG_INFO(1, "Server: stop%s", "\n");
			exit(EXIT_SUCCESS);
		}
		auto header = datagram.getHeader();
		LOG_INFO(1, "Server: Got header: seq_number - %d, seq_total - %d, type - %d\n", header.seq_number, header.seq_total, header.type);
	} catch (exception& ex) {
		cerr << ex.what() << endl;
	}
	return datagram;
}
