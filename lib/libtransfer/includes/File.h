#pragma once

#include <vector>
#include <cstddef>
#include <limits>
#include <cstring>
#include <cstdint>
#include "Datagram.h"
#include "Header.h"

using datagrams = std::vector<Datagram>;

class File {
public:
	File();
	void							addDatagram(Datagram datagram);
	const datagrams&	getDatagrams(void) const;
	const std::byte		*getId(void) const;
private:
	static std::byte	id_[8];
	datagrams					data_;
};
