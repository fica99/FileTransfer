#pragma once
#include "IDatagram.h"
#include "Header.h"
#include "Serialize.h"
#include <memory>
#include <cstring>

class Datagram : public IDatagram {
public:
	Datagram(size_t	datagram_size, Header header);
	~Datagram() override = default;
	size_t					getDatagramSize() const override;
	size_t					setMessage(const char *msg);
	bytes						getDatagram(void) const override;
private:
	size_t			datagram_size_;
	Header			header_;
	size_t			current_size_;
	bytes				datagram_;
};
