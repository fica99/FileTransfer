#pragma once

#include <vector>
#include <stdexcept>
#include <fstream>
#include <cstddef>
#include "Header.h"
#include "Datagram.h"
#include "CRC.h"

using datagrams = std::vector<Datagram>;

class File {
public:
	File(const std::string& filename, size_t datagram_size,
																const Header& header);
	File() = default;
	datagrams&					getDatagrams(void);
	void								getContent(std::byte *buff) const;
	size_t							getContentSize(void) const;
	const std::string&	getFilename(void) const;
private:
	std::string					filename_;
	datagrams						data_;
};

uint32_t	crc32cFile(uint32_t crc, const File& file);
