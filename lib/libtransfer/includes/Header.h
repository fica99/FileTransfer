#pragma once

#include <cstdint>
#include <cstddef>
#include <cstring>
#include "Serialize.h"

class IHeader {
public:
	virtual ~IHeader(void);
	virtual std::byte	*serialize(std::byte *buff) const;
};


struct Header : IHeader {
	uint32_t	seq_number;
	uint32_t	seq_total;
	uint8_t		type;
	std::byte	id[8];
	~Header(void) override = default;
	std::byte	*serialize(std::byte *buff) const override;
};
