#include "Datagram.h"

using namespace	std;

Datagram::Datagram(size_t datagram_size, size_t header_size) :
											datagram_size_(datagram_size),
											header_size_(header_size),
											content_size_(0),
											datagram_(new byte[datagram_size + 1]) {
}

void		Datagram::setContent(const char *content) {
	size_t	content_max_size;

	content_max_size = getContentMaxSize();
	while (content[content_size_] &&
		content_size_ < content_max_size) {
		datagram_.get()[header_size_ + content_size_] =
								static_cast<byte>(content[content_size_]);
		++content_size_;
	}
}

void		Datagram::setHeader(const char *header) {
	size_t	i;

	i = 0;
	while (header[i] && i < header_size_) {
		datagram_.get()[i] =
								static_cast<byte>(header[i]);
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




//byte	*Serialize::serialize(const Header& header, byte *datagram) {

//	auto end = serialize(header.seq_number, datagram);
//	end = serialize(header.seq_total, end);
//	end = serialize(header.type, end);
//	memcpy(end, header.id, sizeof(header.id));
//	return datagram + sizeof(header.id);
//}

//size_t	Send::sending(const Socket& sock, const IDatagram& datagram) {
//	auto data = datagram.getDatagram();
//	auto size = datagram.getDatagramSize();
//	return sending(sock, static_cast<void*>(data.get()), size);
//}
