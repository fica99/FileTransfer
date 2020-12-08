#include "client.h"

using namespace	std;

static void	printUsage(void) {
	cerr << "usage: ./FileClient -i host -p port -f file ..." << endl;
	exit(EXIT_FAILURE);
}

static vector<string>	parseArgs(int argc, char **argv, char **ip, char **serv_port) {
	int									rez;
	int									index;
	vector<string>			filenames;

	while ((rez = getopt(argc, argv, "i:p:f:")) != -1) {
		switch (rez) {
			case 'i': *ip = optarg; break;
			case 'p': *serv_port = optarg; break;
			case 'f':
				index = optind - 1;
				while(index < argc && *argv[index] != '-')
					filenames.push_back(string(argv[index++]));
				break;
			case '?': printUsage();
		}
	}
	if (!*ip || !*serv_port || filenames.empty())
		printUsage();
	return filenames;
}

int	main(int argc, char **argv) {
	char						*ip = NULL;
	char						*serv_port = NULL;

	vector<string> filenames = parseArgs(argc, argv, &ip, &serv_port);
	sendFiles(ip, serv_port, move(filenames));
	return (0);
}
