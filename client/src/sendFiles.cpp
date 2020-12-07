#include "client.h"

using namespace	std;

static Header	getConfirmation(const Socket& sock) {
	Header		header;
	byte			buff[header.size()];

	Recv::recving(sock, buff, header.size());
	deserialize_header(header, buff);
	return header;
}

static void	sendDatagram(const Socket& sock, const Datagram& datagram) {
	try {
		Header	sended;

		deserialize_header(sended, datagram.getDatagram().get());
		Send::sending(sock, datagram.getDatagram().get(),
														datagram.getDatagramSize());
		Header	got = getConfirmation(sock);

	} catch (exception& ex) {
		cerr << ex.what() << endl;
	}
}

static void	sendFile(const Socket& sock, File& file) {
	size_t	i;

	for (auto& datagram : file.getDatagrams()) {
		sendDatagram(sock, datagram);
		LOG_INFO(1, "Send datagram: size %ld, file %s\n",
			datagram.getDatagramSize(), file.getFilename().c_str());
	}
}

void				sendFiles(const char *ip, const char *serv_port,
											vector<File> files) {
	Socket								sock(AddrInfo(ip, serv_port, SOCK_DGRAM));
	vector<future<void>>	futures;

	LOG_INFO(1, "Create socket to send on: ip - %s port, - %s\n", ip, serv_port);
	for (auto& file : files) {
		futures.push_back(async(sendFile, ref(sock), ref(file)));
	}
}
