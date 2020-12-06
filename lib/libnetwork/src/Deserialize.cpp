#include "Deserialize.h"

using namespace	std;

byte	*deserialize(std::byte *datagram, uint32_t& nb) {
	size_t size_int = sizeof(nb);
	memcpy(&nb, datagram, size_int);
	nb = ntohl(nb);
	return datagram + size_int;

}

byte	*deserialize(std::byte *datagram, uint8_t& nb) {
	size_t size_char = sizeof(nb);
	memcpy(&nb, datagram, size_char);
	return datagram + size_char;
}
