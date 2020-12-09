#include "server.h"

using namespace	std;

static void	printUsage(void) {
	cerr << "usage: ./FileServer -p port" << endl;
	exit(EXIT_FAILURE);
}

static void	parseArgs(int argc, char **argv, char **serv_port) {
	int	rez;

	while ((rez = getopt(argc, argv, "p:")) != -1) {
		switch (rez) {
			case 'p': *serv_port = optarg; break;
			case '?': printUsage();
		}
	}
	if (!*serv_port)
		printUsage();
}

static void	serverLoop(Socket sock) {
	struct sockaddr	from;
	socklen_t				from_len;
	vector<File>		files;

	while (true) {
		Datagram datagram = getDatagram(sock.getSocketFd(), &from, &from_len);
		auto& file = addDatagram(files, datagram);
		auto confirmation = confirmDatagram(file, datagram);
		sendDatagram(sock.getSocketFd(), &from, &from_len, confirmation);
	}
}

static Socket	createSocket(const char *serv_port) {
	AddrInfo	info(NULL, serv_port, SOCK_DGRAM);
	const addrinfo *struct_info = info.getAddrInfo();
	Socket		sock(struct_info->ai_family,
							struct_info->ai_socktype,
							struct_info->ai_protocol
						);

	sock.binding(struct_info->ai_addr, struct_info->ai_addrlen);
	return sock;
}

int	main(int argc, char **argv) {
	char	*serv_port = NULL;

	parseArgs(argc, argv, &serv_port);
	serverLoop(createSocket(serv_port));
	return (0);
}
