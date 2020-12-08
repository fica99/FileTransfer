#include "Header.h"

using namespace	std;

size_t	Header::size(void) const {
	return sizeof(seq_number) + sizeof(seq_total)
		+ sizeof(type) + sizeof(id);
}

byte	*serializeHeader(const Header& header, byte *buff) {
	auto end = Serialize::serialize(header.seq_number, buff);
	end = Serialize::serialize(header.seq_total, end);
	end = Serialize::serialize(header.type, end);
	memcpy(end, header.id, sizeof(header.id));
	return end + sizeof(header.id);
}

byte	*deserializeHeader(Header& header, byte *buff) {
	auto end = Deserialize::deserialize(header.seq_number, buff);
	end = Deserialize::deserialize(header.seq_total, end);
	end = Deserialize::deserialize(header.type, end);
	memcpy(header.id, end, sizeof(header.id));
	return end + sizeof(header.id);
}
