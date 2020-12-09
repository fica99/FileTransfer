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

bool		Datagram::operator==(const Datagram& other) const {
	if (make_tuple(header_, datagram_max_size_, content_size_)
	== make_tuple(other.header_, other.datagram_max_size_, other.content_size_))
		if (!memcmp(datagram_.get(), other.datagram_.get(), content_size_))
			return true;
	return false;
}

size_t	Datagram::send(Socket& sock) const {
	return Send::sending(sock, datagram_.get(), getDatagramSize());
}

size_t	Datagram::recv(Socket& sock) {
	size_t got_bytes;

	got_bytes = Recv::recving(sock, datagram_.get(), datagram_max_size_);
	header_.deserialize(datagram_.get());
	return got_bytes;
}
