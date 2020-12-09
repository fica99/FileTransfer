#include "server.h"

using namespace	std;

static uint32_t	calcCheckSum(File& file) {
	byte			buff[file.getContentSize()];
	uint32_t	checkSum;

	file.getContent(buff);
	checkSum = CRC::crc32c(0, buff, file.getContentSize());
	return checkSum;
}

Datagram	confirmDatagram(File& file, const Datagram& datagram) {
	Datagram	confirmation(DATAGRAM_SIZE);
	Header		header;

	header.type = ACK_TYPE;
	header.seq_number = datagram.getHeader().seq_number;
	header.seq_total = file.getDatagrams().size();
	memcpy(header.id, datagram.getHeader().id, sizeof(header.id));
	confirmation.setHeader(move(header));
	if (file.getDatagrams().size() == datagram.getHeader().seq_total) {
		uint32_t checkSum = calcCheckSum(file);
		byte			buff[sizeof(checkSum)];

		Serialize::serialize(checkSum, buff);
		confirmation.setContent(buff, sizeof(buff));
		LOG_INFO(1, "Server: File is full: checksum - %ud\n", checkSum);
	}
	return confirmation;
}
