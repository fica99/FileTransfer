#include "Datagram.h"

using namespace	std;

Datagram::Datagram(size_t datagram_size, Header header) :
											datagram_size_(datagram_size),
											header_(move(header)),
											current_size_(0) {
	datagram_ = bytes(new byte[datagram_size]);
	Serialize::serialize(header_, datagram_.get());
}

size_t	Datagram::getDatagramSize() const {
	return datagram_size_;
}

size_t	Datagram::setMessage(const char *msg) {
	auto end = static_cast<byte*>(
							memcpy(datagram_.get() + current_size_,
							msg, datagram_size_ - current_size_)
							);
	return end - (datagram_.get() + current_size_);
}

bytes		Datagram::getDatagram(void) const {
	return datagram_;
}
