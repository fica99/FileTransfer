#include "Deserialize.h"

using namespace	std;

const byte	*Deserialize::deserialize(uint32_t& nb, const std::byte *buff) {
	size_t size_int = sizeof(nb);
	memcpy(&nb, buff, size_int);
	nb = ntohl(nb);
	return buff + size_int;
}

const byte	*Deserialize::deserialize(uint8_t& nb, const std::byte *buff) {
	size_t size_char = sizeof(nb);
	memcpy(&nb, buff, size_char);
	return buff + size_char;
}
