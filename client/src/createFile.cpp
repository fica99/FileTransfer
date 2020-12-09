#include "client.h"

using namespace	std;

static const byte	*getId(void) {
	static byte	id_[8];

	int	size_id = sizeof(id_);
	while (size_id--) {
		unsigned char tmp = to_integer<unsigned char>(id_[size_id]);
		if (tmp != numeric_limits<unsigned char>::max()) {
			++tmp;
			id_[size_id] = static_cast<byte>(tmp);
			break;
		}
	}
	return id_;
}

File			createFile(const string& filename) {
	File		file(filename, DATAGRAM_SIZE);
	Header	header;

	auto& datagrams = file.getDatagrams();
	memcpy(header.id, getId(), sizeof(header.id));
	header.seq_total = datagrams.size();
	header.seq_number = 0;
	header.type = PUT_TYPE;
	for (auto& datagram : datagrams) {
		datagram.setHeader(header);
		++header.seq_number;
	}
	LOG_INFO(1, "Client: Read file %s, number_of_datagrams - %ld, content_size - %ld\n", filename.c_str(), file.getDatagrams().size(), file.getContentSize());
	return file;
}
