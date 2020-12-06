#pragma once

#include <cstdint>
#include <cstddef>
#include <cstring>
#include <netinet/in.h>

class Deserialize{
public:
	static std::byte	*deserialize(std::byte *datagram, uint32_t& nb);
	static std::byte	*deserialize(std::byte *datagram, uint8_t& nb);
};
