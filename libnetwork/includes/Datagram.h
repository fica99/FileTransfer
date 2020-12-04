#pragma once

#include <cstdint>
#include <cstddef>

class Datagram {
	virtual ~Datagram();
	virtual size_t	getDatagramSize() const = 0;
};

class MyDatagram : public Datagram {
public:
	MyDatagram(size_t datagram_size);
	~MyDatagram() = default;
private:
	size_t	datagram_size_;
};
