#pragma once

#include <netinet/in.h>
#include <cstring>
#include <cstddef>

class Serialize {
public:
	static std::byte	*serialize(uint32_t hostlong, std::byte *datagram);
	static std::byte	*serialize(uint8_t nb, std::byte *datagram);
};
