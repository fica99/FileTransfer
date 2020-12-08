#include "client.h"

using namespace	std;

static bool	isConfirmed(const Socket& sock, const Datagram& datagram) {
	Header	get_header;
	Header	send_header;
	byte		buff[send_header.size()];

	deserializeHeader(send_header, datagram.getDatagram().get());
	LOG_INFO(1, "Send header: seq_number - %d, seq_total - %d, type - %d\n", send_header.seq_number, send_header.seq_total, send_header.type);
	size_t get_bytes = Recv::recving(sock, buff, send_header.size());
	LOG_INFO(1, "Got %ld bytes\n", get_bytes);
	if (get_header.size() > get_bytes)
		return false;
	deserializeHeader(get_header, buff);
	LOG_INFO(1, "Got header: seq_number - %d, seq_total - %d, type - %d\n", get_header.seq_number, get_header.seq_total, get_header.type);
	if (get_header.type != ACK_TYPE
		|| memcmp(get_header.id, send_header.id, sizeof(send_header.id))
		|| get_header.seq_number != send_header.seq_number)
		return false;
	return true;
}

static void	sendDatagram(const Socket& sock, const Datagram& datagram) {
	try {
		do {
			size_t size_datagram = datagram.getDatagramSize();
			size_t nb_sended_bytes = Send::sending(sock,
											datagram.getDatagram().get(), size_datagram);
			LOG_INFO(1, "Send %ld bytes, datagram of size %ld\n", nb_sended_bytes, size_datagram);
		} while (!isConfirmed(sock, datagram));
	} catch (exception& ex) {
		cerr << ex.what() << endl;
	}
}

static void	sendFile(const Socket& sock, File& file) {
	for (auto& datagram : file.getDatagrams()) {
		sendDatagram(sock, datagram);
		LOG_INFO(1, "Send datagram: size %ld, file %s\n", datagram.getDatagramSize(), file.getFilename().c_str());
	}
}

void				sendFiles(const char *ip, const char *serv_port,
											vector<File> files) {
	Socket								sock(AddrInfo(ip, serv_port, SOCK_DGRAM));
	vector<future<void>>	futures;

	sock.setTimeout(RECV_TIMEOUT_SEC, RECV_TIMEOUT_MICROSEC);
	LOG_INFO(1, "Create socket to send on: ip - %s port, - %s\n", ip, serv_port);
	for (auto& file : files) {
		sendFile(sock, file);
		//futures.push_back(async(sendFile, ref(sock), ref(file)));
	}
}
