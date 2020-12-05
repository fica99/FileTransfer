#pragma once

#include <cstdint>
#include <cstddef>

struct Header {
	uint32_t	seq_number;
	uint32_t	seq_total;
	uint8_t		type;
	std::byte	id[8];
};
