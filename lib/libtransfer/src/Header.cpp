#include "Header.h"

using namespace	std;

size_t	Header::size(void) const {
	return sizeof(seq_number) + sizeof(seq_total)
		+ sizeof(type) + sizeof(id);
}



byte	*serialize_header(const Header& header, std::byte *buff) {
	auto end = Serialize::serialize(header.seq_number, buff);
	end = Serialize::serialize(header.seq_total, end);
	end = Serialize::serialize(header.type, end);
	memcpy(end, header.id, sizeof(header.id));
	return end + sizeof(header.id);
}

byte	*deserialize_header(Header& header, std::byte *buff) {
	auto end = Deserialize::deserialize(buff, header.seq_number);
	auto end = Deserialize::deserialize(end, header.seq_total);
	auto end = Deserialize::deserialize(end, header.type);
	memcpy(header.id, end, sizeof(header.id));
	return end + sizeof(header.id);
}
