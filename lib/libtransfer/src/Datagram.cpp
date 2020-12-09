#include "Datagram.h"

using namespace	std;

Datagram::Datagram(size_t datagram_max_size) :
											datagram_max_size_(datagram_max_size),
											content_size_(0),
											datagram_(new byte[datagram_max_size]) {
}

Datagram::Datagram(Datagram&& other) : header_(move(other.header_)),
																			datagram_max_size_(other.datagram_max_size_),
																			content_size_(other.content_size_),
																			datagram_(move(other.datagram_)) {
}

Datagram::Datagram(const Datagram& other) : header_(other.header_),
																			datagram_max_size_(other.datagram_max_size_),
																			content_size_(other.content_size_),
																			datagram_(other.datagram_) {
}

Datagram&	Datagram::operator=(Datagram&& other) {
	header_ = move(other.header_);
	datagram_max_size_ = other.datagram_max_size_;
	content_size_ = other.content_size_;
	datagram_ = move(other.datagram_);
	return *this;
}

Datagram&	Datagram::operator=(const Datagram& other) {
	header_ = other.header_;
	datagram_max_size_ = other.datagram_max_size_;
	content_size_ = other.content_size_;
	datagram_ = other.datagram_;
	return *this;
}


void		Datagram::setContent(const byte *content, size_t content_size) {
	size_t	content_max_size;
	size_t	header_size = header_.size();

	content_max_size = getContentMaxSize();
	while (content_size_ < content_max_size &&
							content_size_ < content_size) {
		datagram_.get()[header_size + content_size_] =
						content[content_size_];
		++content_size_;
	}
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

size_t	Datagram::send(int fd, const struct sockaddr *dest_addr,
												socklen_t dest_len) const {
	return Send::sendall(fd, datagram_.get(), getDatagramSize(), dest_addr, dest_len);
}

size_t	Datagram::recv(int fd, struct sockaddr *from, socklen_t* from_len) {
	size_t got_bytes;

	got_bytes = Recv::recvall(fd, datagram_.get(), datagram_max_size_, from, from_len);
	if (got_bytes) {
		header_.deserialize(datagram_.get());
		content_size_ = got_bytes - header_.size();
	}
	return got_bytes;
}
