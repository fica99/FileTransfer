#include "File.h"

using namespace	std;


File::File(const string& filename, size_t datagram_size) {
	ifstream	file(filename);

	if (!file)
		throw invalid_argument(filename + " does not exist");
	while (!file.eof())
		addDatagram(createDatagram(file, datagram_size));
	initId();
}

Datagram	File::createDatagram(ifstream& file, size_t datagram_size) {
	Header		header;
	Datagram	datagram(datagram_size, header.size());
	char			buff[datagram_size + 1];

	file.read(buff, datagram.getContentMaxSize());
	datagram.setContent(buff);
	return datagram;
}


void	File::initId(void) {
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
