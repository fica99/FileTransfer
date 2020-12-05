#include "Serialize.h"

using namespace	std;

template <typename T>
byte	*Serialize::serialize(T nb, byte *datagram) {
	T	tmp = htonl(nb);
	size_t size_tmp = sizeof(tmp);
	return static_cast<byte*>(memcpy(datagram, &tmp, size_tmp));
}


byte	*Serialize::serialize(const Header& header, byte *datagram) {

	auto end = serialize(header.seq_number, datagram);
	end = serialize(header.seq_total, end);
	end = serialize(header.type, end);
	return static_cast<byte*>(memcpy(end, header.id, sizeof(header.id)));
}
