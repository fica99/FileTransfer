#include "Header.h"

using namespace	std;

byte	*Header::serialize(std::byte *buff) const {
	auto end = Serialize::serialize(seq_number, buff);
	end = Serialize::serialize(seq_total, end);
	end = Serialize::serialize(type, end);
	memcpy(end, id, sizeof(id));
	return buff + sizeof(id);
}

size_t	Header::size(void) const {
	return sizeof(seq_number) + sizeof(seq_total)
		+ sizeof(type) + sizeof(id);
}

byte	*serialize_header(const IHeader& header, byte *buff) {
	return header.serialize(buff);
}

