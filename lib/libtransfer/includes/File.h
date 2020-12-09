#pragma once

#include <vector>
#include <stdexcept>
#include <fstream>
#include <cstddef>
#include "Datagram.h"

using datagrams = std::vector<Datagram>;

class File {
public:
	File(const std::string& filename, size_t datagram_size);
	File() = default;
	datagrams&					getDatagrams(void);
	void								getContent(std::byte *buff) const;
	size_t							getContentSize(void) const;
	const std::string&	getFilename(void) const;
private:
	std::string					filename_;
	datagrams						data_;
};
