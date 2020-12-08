#pragma once

#include <cstdint>
#include <cstddef>
#include <cstring>
#include "Serialize.h"
#include "Deserialize.h"

struct Header {
public:
	size_t		size() const;
	uint32_t	seq_number;
	uint32_t	seq_total;
	uint8_t		type;
	std::byte	id[8];
};

std::byte	*serializeHeader(const Header& header, std::byte *buff);
std::byte	*deserializeHeader(Header& header, std::byte *buff);
