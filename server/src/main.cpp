#include "server.h"

using namespace	std;

#include <arpa/inet.h>

void *get_in_addr(const struct sockaddr *sa) {
	if (sa->sa_family == AF_INET)
		return &(((struct sockaddr_in*)sa)->sin_addr);
	return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

int	main(int argc, char **argv) {
	(void)argc;
	(void)argv;
	Socket	sock(AddrInfo(NULL, SERV_PORT, SOCK_DGRAM));
	char s[INET6_ADDRSTRLEN];
	const addrinfo *sa = sock.getSocketInfo();

	inet_ntop(sa->ai_family, get_in_addr((const struct sockaddr *)sa->ai_addr), s, sizeof s);
	printf("client: connecting to %s\n", s);
	return 0;
}

