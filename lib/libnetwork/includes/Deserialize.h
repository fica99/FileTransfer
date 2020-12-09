#pragma once

#include <cstdint>
#include <cstddef>
#include <cstring>
#include <netinet/in.h>

class Deserialize {
public:
	static const std::byte	*deserialize(uint32_t& nb, const std::byte *buff);
	static const std::byte	*deserialize(uint8_t& nb, const std::byte *buff);
};
