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

std::byte	*deserialize_header(Header& header, std::byte *buff);
std::byte	*serialize_header(const Header& header, std::byte *buff);

