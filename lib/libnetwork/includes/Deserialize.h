#pragma once

#include <cstdint>
#include <cstddef>
#include <cstring>
#include <netinet/in.h>

class Deserialize {
public:
	static std::byte	*deserialize(uint32_t& nb, std::byte *buff);
	static std::byte	*deserialize(uint8_t& nb, std::byte *buff);
};
