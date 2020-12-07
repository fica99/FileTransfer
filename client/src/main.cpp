#include "client.h"

using namespace	std;

static void	printUsage(void) {
	cerr << "usage: ./FileClient -i host -p port -f file ..." << endl;
	exit(EXIT_FAILURE);
}

static vector<string>	parseArgs(int argc, char **argv, char **ip, char **port) {
	int									rez;
	int									index;
	vector<string>			filenames;

	while ((rez = getopt(argc, argv, "i:p:f:")) != -1) {
		switch (rez) {
			case 'i': *ip = optarg; break;
			case 'p': *port = optarg; break;
			case 'f':
				index = optind - 1;
				while(index < argc && *argv[index] != '-')
					filenames.push_back(string(argv[index++]));
				break;
			case '?': printUsage();
		}
	}
	if (!*ip || !*port || filenames.empty())
		printUsage();
	return filenames;
}

static const byte	*getId(void) {
	static byte	id_[8];

	int	size_id = sizeof(id_);
	while (size_id--) {
		unsigned char tmp = to_integer<unsigned char>(id_[size_id]);
		if (tmp != numeric_limits<unsigned char>::max()) {
			++tmp;
			id_[size_id] = static_cast<byte>(tmp);
			break;
		}
	}
	return id_;
}

static File	createFile(const string& filename) {
	Header	header;
	File		file(filename, DATAGRAM_SIZE, header.size());
	byte		buff[header.size() + 1];

	auto& datagrams = file.getDatagrams();
	memcpy(header.id, getId(), sizeof(header.id));
	header.seq_total = datagrams.size();
	header.seq_number = 0;
	header.type = PUT_TYPE;
	for (auto& datagram : datagrams) {
		serialize_header(header, buff);
		datagram.setHeader(buff);
		++header.seq_number;
	}
	return file;
}

static void					printFileInfo(File& file, const string& filename) {
	size_t content_size = file.getContentSize();
	byte	buff[content_size + 1];

	file.getContent(buff);
	LOG_INFO(1, "Read file %s, number_of_datagrams - %ld, content_size - %ld, crc32c - %d\n",
		filename.c_str(), file.getDatagrams().size(),
				content_size, CRC::crc32c(0, buff, content_size));

}


static vector<File>	createFiles(vector<string> filenames) {
	vector<File>			files;

	for (auto& filename : filenames) {
		try {
			File file = createFile(filename);
			printFileInfo(file, filename);
			files.push_back(move(file));
		} catch (exception& ex) {
			cerr << ex.what() << endl;
		}
	}
	return files;
}

int	main(int argc, char **argv) {
	char						*ip = NULL;
	char						*port = NULL;

	vector<string> filenames = parseArgs(argc, argv, &ip, &port);
	vector<File> files = createFiles(move(filenames));
	//sendFiles(ip, port, filenames);

	return (0);
}
