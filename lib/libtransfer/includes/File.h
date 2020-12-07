#pragma once

#include <vector>
#include <cstddef>
#include <limits>
#include <cstring>
#include <cstdint>
#include "Datagram.h"
#include <stdexcept>
#include <fstream>

using datagrams = std::vector<Datagram>;

class File {
public:
	File(const string& filename, size_t datagram_size);
	const datagrams&	getDatagrams(void) const;
	const std::byte		*getId(void) const;
private:
	void							addDatagram(Datagram datagram);
	Datagram					createDatagram(ifstream& file, size_t datagram_size);
	void							initId(void);
	static std::byte	id_[8];
	datagrams					data_;
};
