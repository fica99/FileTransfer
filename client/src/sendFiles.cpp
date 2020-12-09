#include "client.h"

using namespace	std;

static void	shuffleDatagrams(datagrams& datagrams) {
	random_device rd;
	mt19937 g(rd());
	shuffle(datagrams.begin(), datagrams.end(), g);
}

static bool	isConfirmed(const Socket& sock, File& file) {
	auto& datagrams = file.getDatagrams();
	Datagram				datagram(DATAGRAM_SIZE);
	struct sockaddr	address;
	socklen_t				address_len;
	Header					header;

	size_t got_bytes = datagram.recv(sock.getSocketFd(), &address, &address_len);
	LOG_INFO(1, "Client: Got %ld bytes\n", got_bytes);
	header = datagram.getHeader();
	if (got_bytes < header.size())
		return false;
	if (datagrams.size() == header.seq_total){
		uint32_t check_sum = file.crc32c(0);
		uint32_t check_sum_get = 0;
		Deserialize::deserialize(check_sum_get, datagram.getContent());
		LOG_INFO(1, "Check sum: had - %u, got - %u\n", check_sum, check_sum_get);
		if (check_sum != check_sum_get)
			return false;
		return true;
	}
	return false;
}

static void	sendFile(const Socket& sock, const AddrInfo& info, File file) {
	auto& datagrams = file.getDatagrams();
	shuffleDatagrams(datagrams);
	while (true) {
		for (auto& datagram : datagrams) {
			sendDatagram(sock, info, datagram);
			LOG_INFO(1, "Client: Send datagram: size - %ld, filename - %s, header: seq_total - %d, seq_number - %d\n", datagram.getDatagramSize(), file.getFilename().c_str(), datagram.getHeader().seq_total, datagram.getHeader().seq_number);
			if (isConfirmed(sock, file)) {
				LOG_INFO(1, "Client: Send file: size - %ld, number of datagrams - %ld, filename -  %s\n", file.getContentSize(), file.getDatagrams().size() ,file.getFilename().c_str());
				return ;
			}
		}
	}
}

void				sendFiles(const char *ip, const char *serv_port,
																						vector<string> filenames) {
	AddrInfo	info(ip, serv_port, SOCK_DGRAM);
	Socket		sock(info.getAddrInfo()->ai_family,
							info.getAddrInfo()->ai_socktype,
							info.getAddrInfo()->ai_protocol
						);

	sock.setTimeout(RECV_TIMEOUT_SEC, RECV_TIMEOUT_MICROSEC);
	for (auto& filename : filenames) {
		try {
			auto file = createFile(filename);
			sendFile(sock, info, move(file));
		} catch (exception& ex) {
			cerr << ex.what() << endl;
		}
	}
}
