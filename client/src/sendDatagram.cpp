#include "client.h"

using namespace	std;

static bool	isConfirmedDatagram(Socket& sock, const Datagram& datagram) {
	Datagram	confirmation(DATAGRAM_SIZE);

	auto& send_header = datagram.getHeader();
	LOG_INFO(1, "Client: Send header: seq_number - %d, seq_total - %d, type - %d\n", send_header.seq_number, send_header.seq_total, send_header.type);
	size_t get_bytes = confirmation.recv(sock);
	LOG_INFO(1, "Client: Got %ld bytes\n", get_bytes);
	if (confirmation.getHeader().size() > get_bytes) {
		LOG_INFO(1, "Client: Requet timeout (for datagram confirmation)%s", "\n");
		return false;
	}
	auto& got_header = confirmation.getHeader();
	LOG_INFO(1, "Client: Got header: seq_number - %d, seq_total - %d, type - %d\n", got_header.seq_number, got_header.seq_total, got_header.type);
	if (got_header.type != ACK_TYPE
		|| memcmp(got_header.id, send_header.id, sizeof(send_header.id))
		|| got_header.seq_number != send_header.seq_number)
		return false;
	return true;
}

void	sendDatagram(Socket& sock, const Datagram& datagram) {
	try {
		do {
			size_t nb_sended_bytes = datagram.send(sock);
			LOG_INFO(1, "Client: Send %ld bytes, datagram of size %ld\n", nb_sended_bytes, datagram.getContentSize());
		} while (!isConfirmedDatagram(sock, datagram));
	} catch (exception& ex) {
		cerr << ex.what() << endl;
	}
}
