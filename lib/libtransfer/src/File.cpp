#include "File.h"

using namespace	std;

File::File() {
	int	size_id = sizeof(id_);

	while (size_id--) {
		unsigned char tmp = to_integer<unsigned char>(id_[size_id]);
		if (tmp != numeric_limits<unsigned char>::max()) {
			++tmp;
			id_[size_id] = static_cast<byte>(tmp);
			break;
		}
	}
}

void	File::addDatagram(Datagram datagram) {
	data_.push_back(move(datagram));
}

const datagrams&	File::getDatagrams(void) const {
	return data_;
}

const byte		*File::getId(void) const {
	return id_;
}
