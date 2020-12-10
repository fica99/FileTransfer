#include "server.h"

using namespace	std;

Datagram	confirmDatagram(File& file, const Datagram& datagram) {
	Datagram	confirmation(DATAGRAM_SIZE);
	Header		header = datagram.getHeader();
	size_t		seq_total;

	seq_total = header.seq_total;
	header.type = ACK_TYPE;
	header.seq_total = file.getDatagrams().size();
	confirmation.setHeader(header);
	if (file.getDatagrams().size() == seq_total) {
		uint32_t	checkSum = crc32cFile(0, file);
		byte			buff[sizeof(checkSum)];

		Serialize::serialize(checkSum, buff);
		confirmation.setContent<byte>(buff, sizeof(buff));
		LOG_INFO(1, "Server: File is full: checksum - %u\n", checkSum);
	}
	return confirmation;
}
