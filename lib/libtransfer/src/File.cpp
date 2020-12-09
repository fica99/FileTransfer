#include "File.h"

using namespace	std;

File::File(const string& filename, size_t datagram_size)
							: filename_(filename) {
	ifstream	file(filename);
	char			buff[datagram_size + 1];

	if (!file)
		throw invalid_argument(filename + " does not exist");
	while (!file.eof()) {
		Datagram	datagram(datagram_size);

		file.read(buff, datagram.getContentMaxSize());
		datagram.setContent(buff, file.gcount());
		data_.push_back(move(datagram));
	}
}

File::File(File&& other) : filename_(move(other.filename_)),
														data_(move(other.data_)) {
}

File&	File::operator=(File&& other) {
	filename_ = move(other.filename_);
	data_ = move(other.data_);
	return *this;
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


uint32_t	File::crc32c(uint32_t crc) const {
	size_t	content_size = getContentSize();
	byte		buff[content_size];

	getContent(buff);
	return CRC::crc32c(crc, buff, content_size);
}
