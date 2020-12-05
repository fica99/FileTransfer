#pragma once

#include "Header.h"
#include <netinet/in.h>
#include <cstring>

class Serialize {
public:
	template <typename T>
	static std::byte	*serialize(T nb, std::byte *datagram);
	static std::byte	*serialize(const Header& header, std::byte *datagram);
};
