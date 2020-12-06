#include "Datagram.h"

using namespace	std;

Datagram::Datagram(size_t datagram_size, size_t header_size) :
											datagram_size_(datagram_size),
											header_size_(header_size),
											content_size_(0),
											datagram_(new byte[datagram_size + 1]) {
}

void		Datagram::setContent(const byte *content) {
	size_t	content_max_size;

	content_max_size = getContentMaxSize();
	while (to_integer<int>(content[content_size_]) &&
		content_size_ < content_max_size) {
		datagram_.get()[header_size_ + content_size_] =
							content[content_size_];
		++content_size_;
	}
}

void		Datagram::setHeader(const byte *header) {
	size_t	i;

	i = 0;
	while (to_integer<int>(header[i]) && i < header_size_) {
		datagram_.get()[i] = header[i];
		++i;
	}
}

bytes		Datagram::getDatagram(void) const {
	return datagram_;
}

size_t	Datagram::getDatagramSize() const {
	return datagram_size_;
}

const byte	*Datagram::getContent() const {
	return datagram_.get() + header_size_;
}

size_t	Datagram::getContentSize() const {
	return content_size_;
}

size_t	Datagram::getContentMaxSize() const {
	return datagram_size_ - header_size_;
}
