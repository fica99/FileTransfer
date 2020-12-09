#include "Serialize.h"

using namespace	std;

byte	*Serialize::serialize(uint32_t hostlong, byte *buff) {
	uint32_t netlong = htonl(hostlong);
	size_t size_int = sizeof(netlong);
	memcpy(buff, &netlong, size_int);
	return buff + size_int;
}

byte	*Serialize::serialize(uint8_t nb, byte *buff) {
	size_t size_char = sizeof(nb);
	memcpy(buff, &nb, size_char);
	return buff + size_char;
}
