#pragma once

#include <vector>
#include <cstddef>
#include <memory>

using bytes = std::shared_ptr<std::byte>;

class IDatagram {
public:
	virtual ~IDatagram() = 0;
	virtual bytes	getDatagram() const = 0;
	virtual size_t	getDatagramSize() const = 0;
};
