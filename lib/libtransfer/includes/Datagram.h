#pragma once

#include <memory>
#include <cstring>
#include <cstddef>

using bytes = std::shared_ptr<std::byte>;

class Datagram {
public:
	Datagram(size_t	datagram_size, size_t header_size);
	void						setContent(const char *content, size_t content_size);
	void						setHeader(const std::byte *header);
	bytes						getDatagram(void) const;
	size_t					getDatagramSize(void) const;
	const std::byte	*getContent(void) const;
	size_t					getContentSize(void) const;
	size_t					getContentMaxSize(void) const;
private:
	size_t					datagram_size_;
	size_t					header_size_;
	size_t					content_size_;
	bytes						datagram_;
};
