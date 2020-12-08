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

static void	serverLoop(const char *serv_port) {
	Socket				sock(AddrInfo("0.0.0.0", serv_port, SOCK_DGRAM));
	vector<File>	files;

	LOG_INFO(1, "Create listen socket: port - %s\n", serv_port);
	Bind::binding(sock);
	LOG_INFO(1, "Bind listen socket%s", "\n");
	while (true) {
		Datagram datagram = getDatagram(sock);
		addDatagram(files, datagram);
	}
}

int	main(int argc, char **argv) {
	char	*serv_port = NULL;

	parseArgs(argc, argv, &serv_port);
	serverLoop(serv_port);
	return (0);
}
