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
	vector<File>	files;
	struct sockaddr	from;
	socklen_t				from_len;

	while (true) {
		auto datagram = getDatagram(sock.getSocketFd(), &from, &from_len);
		auto file = addDatagram(files, datagram);
		auto confirmation = confirmDatagram(file, datagram);
		sendDatagram(sock.getSocketFd(), &from, &from_len, move(confirmation));
	}
}

static Socket	createSocket(const char *serv_port) {
	AddrInfo	info("0.0.0.0", serv_port, SOCK_DGRAM);
	Socket		sock(info.getAddrInfo()->ai_family,
							info.getAddrInfo()->ai_socktype,
							info.getAddrInfo()->ai_protocol
						);

	sock.binding(info.getAddrInfo()->ai_addr,
				info.getAddrInfo()->ai_addrlen);
	return sock;
}

int	main(int argc, char **argv) {
	char	*serv_port = NULL;

	parseArgs(argc, argv, &serv_port);
	serverLoop(createSocket(serv_port));
	return (0);
}
