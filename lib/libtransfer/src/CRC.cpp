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

uint32_t	CRC::crc32c(uint32_t crc, const File& file) {
	size_t	content_size = file.getContentSize();
	byte	buff[content_size];

	file.getContent(buff);
	return crc32c(crc, buff, content_size);
}
