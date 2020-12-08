#include "Header.h"

using namespace	std;

size_t	Header::size(void) const {
	return sizeof(seq_number) + sizeof(seq_total)
		+ sizeof(type) + sizeof(id);
}

byte	*Header::serialize(byte *buff) const {
	auto end = Serialize::serialize(seq_number, buff);
	end = Serialize::serialize(seq_total, end);
	end = Serialize::serialize(type, end);
	memcpy(end, id, sizeof(id));
	return end + sizeof(id);
}

byte	*Header::deserialize(byte *buff) {
	auto end = Deserialize::deserialize(seq_number, buff);
	end = Deserialize::deserialize(seq_total, end);
	end = Deserialize::deserialize(type, end);
	memcpy(id, end, sizeof(id));
	return end + sizeof(id);
}
