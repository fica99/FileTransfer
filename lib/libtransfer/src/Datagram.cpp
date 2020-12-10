#include "Datagram.h"

using namespace	std;

Datagram::Datagram(size_t datagram_max_size) :
											header_size_(0),
											datagram_max_size_(datagram_max_size),
											content_size_(0),
											datagram_(new byte[datagram_max_size]) {
}

void					Datagram::setHeader(const Header& header) {
	header_size_ = header.size();
	serializeHeader(header, datagram_.get());
}

Header				Datagram::getHeader(void) const {
	Header	header;

	deserializeHeader(header, datagram_.get());
	return header;
}

const bytes&	Datagram::getDatagram(void) const {
	return datagram_;
}

size_t				Datagram::getDatagramSize() const {
	return content_size_ + header_size_;
}

const byte		*Datagram::getContent() const {
	return datagram_.get() + header_size_;
}

size_t				Datagram::getContentSize() const {
	return content_size_;
}

size_t				Datagram::getContentMaxSize() const {
	return datagram_max_size_ - header_size_;
}

size_t				Datagram::getDatagramMaxSize(void) const {
	return datagram_max_size_;
}

bool					Datagram::operator==(const Datagram& other) const {
	if (make_tuple(header_size_, datagram_max_size_, content_size_)
	== make_tuple(header_size_, other.datagram_max_size_, other.content_size_))
		if (!memcmp(datagram_.get(), other.datagram_.get(), content_size_))
			return true;
	return false;
}

size_t				sendDatagram(int fd, const Datagram& datagram,
				const struct sockaddr *dest_addr, socklen_t dest_len) {
	return Send::sendall(fd, datagram.getDatagram().get(),
					datagram.getDatagramSize(), dest_addr, dest_len);
}

size_t				recvDatagram(int fd, Datagram& datagram,
				struct sockaddr *from, socklen_t* from_len) {
	size_t	got_bytes;
	size_t	datagram_max_size = datagram.getDatagramMaxSize();
	byte		buff[datagram_max_size + 1];
	Header	header;

	got_bytes = Recv::recvall(fd, buff,
			datagram_max_size, from, from_len);
	if (got_bytes >= header.size()) {
		auto end = deserializeHeader(header, buff);
		datagram.setHeader(header);
		datagram.setContent(end, got_bytes - header.size());
	}
	return got_bytes;
}
