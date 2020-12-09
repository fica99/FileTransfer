#pragma once

#include <cstddef>
#include <cstdint>
#include "File.h"

/* CRC-32C (iSCSI) polynomial in reversed bit order. */
#define POLY 0x82f63b78

/* CRC-32 (Ethernet, ZIP, etc.) polynomial in reversed bit order. */
/* #define POLY 0xedb88320 */

class CRC {
public:
	static uint32_t	crc32c(uint32_t crc,
					const std::byte *buf, size_t len);
	static uint32_t	crc32c(uint32_t crc, const File& file);
};
