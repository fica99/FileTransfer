#include "Datagram.h"

using namespace	std;

Datagram::Datagram(size_t datagram_max_size) :
											datagram_max_size_(datagram_max_size),
											content_size_(0),
											datagram_(new byte[datagram_max_size + 1]) {
}

void		Datagram::setContent(const char *content, size_t content_size) {
	size_t	content_max_size;

	content_max_size = getContentMaxSize();
	while (content_size_ < content_max_size &&
							content_size_ < content_size) {
		datagram_.get()[header_.size() + content_size_] =
						static_cast<byte>(content[content_size_]);
		++content_size_;
	}
}

void		Datagram::setContent(const byte *content, size_t content_size) {
	size_t	content_max_size;

	content_max_size = getContentMaxSize();
	while (content_size_ < content_max_size &&
							content_size_ < content_size) {
		datagram_.get()[header_.size() + content_size_] = content[content_size_];
		++content_size_;
	}
}

void		Datagram::setHeader(Header header) {
	header_ = move(header);
	header.serialize(datagram_.get());
}

const Header&		Datagram::getHeader(void) const {
	return header_;
}

const bytes&	Datagram::getDatagram(void) const {
	return datagram_;
}

size_t	Datagram::getDatagramSize() const {
	return content_size_ + header_.size();
}

const byte	*Datagram::getContent() const {
	return datagram_.get() + header_.size();
}

size_t	Datagram::getContentSize() const {
	return content_size_;
}

size_t	Datagram::getContentMaxSize() const {
	return datagram_max_size_ - header_.size();
}
