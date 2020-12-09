#pragma once

#include <vector>
#include <stdexcept>
#include <fstream>
#include <cstddef>
#include "Datagram.h"
#include "CRC.h"

using datagrams = std::vector<Datagram>;

class File {
public:
	File(const std::string& filename, size_t datagram_size);
	File() = default;
	File(const File& other) = delete;
	File(File&& other);
	File&								operator=(const File& other) = delete;
	File&								operator=(File&& other);
	datagrams&					getDatagrams(void);
	void								getContent(std::byte *buff) const;
	size_t							getContentSize(void) const;
	const std::string&	getFilename(void) const;
	uint32_t						crc32c(uint32_t crc) const;
private:
	std::string					filename_;
	datagrams						data_;
};
