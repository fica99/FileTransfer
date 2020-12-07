#include "client.h"

using namespace	std;

void	printUsage(void) {
	cerr << "usage: ./FileClient -i host -p port -f file ..." << endl;
	exit(EXIT_FAILURE);
}

Datagram	createDatagram(ifstream& file) {
	Header		header;
	Datagram	datagram(DATAGRAM_SIZE, header.size());
	char			buff[DATAGRAM_SIZE + 1];

	file.read(buff, datagram.getContentMaxSize());
	datagram.setContent(buff);
	return datagram;
}

File	createFile(const string& filename) {
	ifstream	file(filename);
	File			file_handler;

	if (!file)
		throw invalid_argument(filename + " does not exist");
	while (!file.eof())
		file_handler.addDatagram(createDatagram(file));
	return file_handler;
}

void	sendFiles(const char *ip, const char *port,
													const vector<string>& file_names) {
	FileClient	client(ip, port);

	for (auto& filename : file_names) {
		try {
			auto file = createFile(filename);

		} catch (exception& ex) {
			cerr << ex.what() << endl;
		}
		// cout << file << endl;
	}
}

int	main(int argc, char **argv) {
	int							rez;
	char						*ip = NULL;
	char						*port = NULL;
	vector<string>	file_names;
	int							index;

	while ((rez = getopt(argc, argv, "i:p:f:")) != -1) {
		switch (rez) {
			case 'i': ip = optarg; break;
			case 'p': port = optarg; break;
			case 'f':
				index = optind - 1;
				while(index < argc && *argv[index] != '-')
					file_names.push_back(string(argv[index++]));
				break;
			case '?': printUsage();
		}
	}
	sendFiles(ip, port, file_names);
	return (0);
}
