#include "Bind.h"


Bind::Bind(Socket& sock) {
	int	fd = sock.getSocketFd();
	int	rv = 1;
	const struct addrinfo	*info = sock.getSocketInfo();

	if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &rv, sizeof(int)) == -1)
		Error{"setsockopt failed"};
	while (bind(fd, info->ai_addr, info->ai_addrlen) == -1)
	{
		sock.createSocket();
		info = sock.getSocketInfo();
		fd = sock.getSocketFd();
	}
}
