#include "Serialize.h"

using namespace	std;

byte	*Serialize::serialize(uint32_t hostlong, byte *datagram) {
	uint32_t netlong = htonl(hostlong);
	size_t size_int = sizeof(netlong);
	memcpy(datagram, &netlong, size_int);
	return datagram + size_int;
}

byte	*Serialize::serialize(uint8_t nb, byte *datagram) {
	size_t size_char = sizeof(nb);
	memcpy(datagram, &nb, size_char);
	return datagram + size_char;
}
