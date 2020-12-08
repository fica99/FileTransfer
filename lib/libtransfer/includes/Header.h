#pragma once

#include <cstdint>
#include <cstddef>
#include <cstring>
#include "Serialize.h"
#include "Deserialize.h"

struct Header {
public:
	size_t		size() const;
	std::byte	*serialize(std::byte *buff) const;
	std::byte	*deserialize(std::byte *buff);
	uint32_t	seq_number;
	uint32_t	seq_total;
	uint8_t		type;
	std::byte	id[8];
};

