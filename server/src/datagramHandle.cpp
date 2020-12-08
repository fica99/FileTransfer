#include "server.h"

using namespace	std;

Datagram	getDatagram(const Socket& sock) {
	byte			buff[DATAGRAM_SIZE];
	Datagram	datagram(DATAGRAM_SIZE);
	Header		header;

	try {
		size_t got_bytes = Recv::recving(sock, buff, DATAGRAM_SIZE);
		LOG_INFO(1, "Got %ld bytes\n", got_bytes);
		header.deserialize(buff);
		LOG_INFO(1, "Got header: seq_number - %d, seq_total - %d, type - %d\n", header.seq_number, header.seq_total, header.type);
		datagram.setHeader(header);
		datagram.setContent(buff + header.size(), got_bytes - header.size());
	} catch (exception& ex) {
		cerr << ex.what() << endl;
	}
	return datagram;
}

void	addDatagram(vector<File>& files, const Datagram& datagram) {
	auto it = find_if(files.begin(), files.end(),
								[&](File& file) {
									if (file.getDatagrams().empty())
										return false;
									return !memcmp(file.getDatagrams().back().getHeader().id,
										datagram.getHeader().id, sizeof(datagram.getHeader().id));
								});
	if (it == files.end())
		files.push_back(File("a", DATAGRAM_SIZE));
	else
		it->getDatagrams().push_back(datagram);
	LOG_INFO(1, "TEST%s", "\n")

}
