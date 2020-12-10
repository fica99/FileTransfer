#include "File.h"

using namespace	std;

File::File(const string& filename, size_t datagram_size, const Header& header)
							: filename_(filename) {
	ifstream	file(filename);
	char			buff[datagram_size];

	if (!file)
		throw invalid_argument(filename + " does not exist");
	while (!file.eof()) {
		Datagram	datagram(datagram_size);

		datagram.setHeader(header);
		file.read(buff, datagram.getContentMaxSize());
		datagram.setContent<char>(buff, file.gcount());
		data_.push_back(move(datagram));
	}
}

datagrams&	File::getDatagrams(void) {
	return data_;
}

const string&	File::getFilename(void) const {
	return filename_;
}

size_t		File::getContentSize(void) const {
	size_t	i = 0;

	for (const auto& datagram : data_)
		i += datagram.getContentSize();
	return i;
}

void			File::getContent(byte *buff) const {
	size_t	i;

	i = 0;
	for (const auto& datagram : data_) {
		memcpy(buff + i, datagram.getContent(), datagram.getContentSize());
		i += datagram.getContentSize();
	}
}


uint32_t	crc32cFile(uint32_t crc, const File& file) {
	size_t	content_size = file.getContentSize();
	byte		buff[content_size];

	file.getContent(buff);
	return CRC::crc32c(crc, buff, content_size);
}
