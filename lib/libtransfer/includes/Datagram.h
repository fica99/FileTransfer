#pragma once

#include <memory>
#include <cstring>
#include <cstddef>
#include <tuple>
#include "Header.h"
#include "Send.h"
#include "Recv.h"

using bytes = std::shared_ptr<std::byte>;

class Datagram {
public:
	Datagram(size_t	datagram_max_size);
	void						setHeader(const Header& header);
	template <typename T>
	void						setContent(const T *content, size_t content_size);
	Header					getHeader(void) const;
	const bytes&		getDatagram(void) const;
	size_t					getDatagramSize(void) const;
	size_t					getDatagramMaxSize(void) const;
	const std::byte	*getContent(void) const;
	size_t					getContentSize(void) const;
	size_t					getContentMaxSize(void) const;
	bool						operator==(const Datagram& other) const;
private:
	size_t					header_size_;
	size_t					datagram_max_size_;
	size_t					content_size_;
	bytes						datagram_;
};

template <typename T>
void	Datagram::setContent(const T *content, size_t content_size) {
	size_t		content_max_size = getContentMaxSize();
	std::byte	*buff = datagram_.get();

	while (content_size_ < content_max_size &&
							content_size_ < content_size) {
		buff[header_size_ + content_size_] =
					static_cast<std::byte>(content[content_size_]);
		++content_size_;
	}
}


size_t	sendDatagram(int fd, const Datagram& datagram,
				const struct sockaddr *dest_addr, socklen_t dest_len);
size_t	recvDatagram(int fd, Datagram& datagram,
				struct sockaddr *from, socklen_t* from_len);
