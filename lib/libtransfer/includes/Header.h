#pragma once

#include <cstdint>
#include <cstddef>
#include <cstring>
#include <tuple>
#include "Serialize.h"
#include "Deserialize.h"

class Header {
public:
	size_t					size() const;
	bool						operator==(const Header& other) const;
	uint32_t				seq_number;
	uint32_t				seq_total;
	uint8_t					type;
	std::byte				id[8];
};

std::byte				*serializeHeader(const Header& header, std::byte *buff);
const std::byte	*deserializeHeader(Header& header, const std::byte *buff);
