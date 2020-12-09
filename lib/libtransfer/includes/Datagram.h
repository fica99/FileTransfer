#pragma once

#include <memory>
#include <cstring>
#include <cstddef>
#include <tuple>
#include "Header.h"
#include "Send.h"
#include "Recv.h"
#include "Socket.h"

using bytes = std::shared_ptr<std::byte>;

class Datagram {
public:
	Datagram(size_t	datagram_max_size);
	void						setContent(const char *content, size_t content_size);
	void						setContent(const std::byte *content, size_t content_size);
	void						setHeader(Header header);
	const Header&		getHeader(void) const;
	const bytes&		getDatagram(void) const;
	size_t					getDatagramSize(void) const;
	const std::byte	*getContent(void) const;
	size_t					getContentSize(void) const;
	size_t					getContentMaxSize(void) const;
	bool						operator==(const Datagram& other) const;
	size_t					send(Socket& sock) const;
	size_t					recv(Socket& sock);
private:
	Header					header_;
	size_t					datagram_max_size_;
	size_t					content_size_;
	bytes						datagram_;
};
