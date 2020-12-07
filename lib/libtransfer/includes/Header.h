#pragma once

#include <cstdint>
#include <cstddef>
#include <cstring>
#include "Serialize.h"

class IHeader {
public:
	virtual ~IHeader(void);
	virtual	size_t		size() const;
	virtual std::byte	*serialize(std::byte *buff) const;
};


struct Header : IHeader {
	~Header(void) override = default;
	size_t		size() const override;
	std::byte	*serialize(std::byte *buff) const override;
	uint32_t	seq_number;
	uint32_t	seq_total;
	uint8_t		type;
	std::byte	id[8];
};

std::byte	*serialize_header(const IHeader& header, std::byte *buff);
