#include "Bind.h"

void	Bind::binding(Socket& sock) {
	int	fd = sock.getSocketFd();
	int	rv = 1;
	const struct addrinfo	*info = sock.getSocketInfo();

	if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &rv, sizeof(int)) == -1)
		ERROR("setsockopt failed");
	while (bind(fd, info->ai_addr, info->ai_addrlen) == -1) {
		fd = sock.updateSocket();
		info = sock.getSocketInfo();
	}
}
