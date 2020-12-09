#include "server.h"

using namespace	std;

Datagram	getDatagram(Socket& sock) {
	Datagram	datagram(DATAGRAM_SIZE);

	try {
		size_t got_bytes = datagram.recv(sock);
		LOG_INFO(1, "Server: Got %ld bytes\n", got_bytes);
		auto& header = datagram.getHeader();
		LOG_INFO(1, "Server: Got header: seq_number - %d, seq_total - %d, type - %d\n", header.seq_number, header.seq_total, header.type);
	} catch (exception& ex) {
		cerr << ex.what() << endl;
	}
	return datagram;
}
