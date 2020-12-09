#include "client.h"

using namespace	std;

static bool	isConfirmedFile(Socket& sock, File& file) {
	uint32_t	check_sum;
	byte			check_sum_get_buff[sizeof(check_sum)];
	uint32_t	check_sum_get;
	size_t		get_bytes;

	check_sum = CRC::crc32c(0, file);
	get_bytes = Recv::recving(sock, check_sum_get_buff, sizeof(check_sum));
	LOG_INFO(1, "Client: Got %ld bytes\n", get_bytes);
	if (sizeof(check_sum) > get_bytes) {
		LOG_INFO(1, "Client: Requet timeout (for file confirmation)%s", "\n");
		return false;
	}
	Deserialize::deserialize(check_sum_get, check_sum_get_buff);
	LOG_INFO(1, "Client: File checksum - %ud, got checksum - %ud\n", check_sum, check_sum_get);
	if (check_sum != check_sum_get)
		return false;
	return true;
}

static void	sendFile(Socket& sock, File file) {
	auto datagrams = file.getDatagrams();
	random_device rd;
	mt19937 g(rd());
	shuffle(datagrams.begin(), datagrams.end(), g);
	do {
		for (auto& datagram : datagrams) {
			sendDatagram(sock, datagram);
			LOG_INFO(1, "Client: Send datagram: size - %ld, filename - %s\n", datagram.getDatagramSize(), file.getFilename().c_str());
		}
	} while (!isConfirmedFile(sock, file));
	LOG_INFO(1, "Client: Send file: size - %ld, number of datagrams - %ld, filename -  %s\n", file.getContentSize(), file.getDatagrams().size() ,file.getFilename().c_str());
}

void				sendFiles(const char *ip, const char *serv_port,
																						vector<string> filenames) {
	Socket	sock(AddrInfo(ip, serv_port, SOCK_DGRAM));

	sock.setTimeout(RECV_TIMEOUT_SEC, RECV_TIMEOUT_MICROSEC);
	LOG_INFO(1, "Client: Create socket to send on: ip - %s, port - %s\n", ip, serv_port);
	for (auto& filename : filenames) {
		try {
			sendFile(sock, createFile(filename));
		} catch (exception& ex) {
			cerr << ex.what() << endl;
		}
	}
}
