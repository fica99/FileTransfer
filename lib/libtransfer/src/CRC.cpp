#include "CRC.h"

using namespace	std;

uint32_t	CRC::crc32c(uint32_t crc, const byte *buf, size_t len)
{
	int k;

	crc = ~crc;
	while (len--) {
		crc ^= to_integer<unsigned char>(*buf);
		++buf;
		for (k = 0; k < 8; k++)
			crc = crc & 1 ? (crc >> 1) ^ POLY : crc >> 1;
	}
	return ~crc;
}
