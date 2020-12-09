#include "server.h"

using namespace	std;

static void	createFile(vector<File>& files, const Datagram& datagram) {
	File	file;

	file.getDatagrams().push_back(datagram);
	files.push_back(move(file));
	LOG_INFO(1, "Server: Create new file, insert datagram%s", "\n")
}

static void	addDatagram2File(File& file, const Datagram& datagram) {
	auto& datagrams = file.getDatagrams();
	auto it = find_if(datagrams.begin(), datagrams.end(),
							[&](const Datagram& dat) {
								return dat == datagram;
							}
						);
	if (it == datagrams.end()) {
		datagrams.push_back(datagram);
		sort(datagrams.begin(), datagrams.end(),
			[](const Datagram& lhs, const Datagram& rhs) {
				return lhs.getHeader().seq_number < rhs.getHeader().seq_number;
			}
		);
		LOG_INFO(1, "Server: Insert datagram to existing file%s", "\n")
	} else
		LOG_INFO(1, "Server: Datagram already exists%s", "\n")
}

File&	addDatagram(vector<File>& files, const Datagram& datagram) {
	auto it = find_if(files.begin(), files.end(),
							[&](File& file) {
								return !memcmp(file.getDatagrams().back().getHeader().id,
								datagram.getHeader().id, sizeof(datagram.getHeader().id));
							}
						);
	if (it == files.end())
		createFile(files, datagram);
	else {
		addDatagram2File(*it, datagram);
		return *it;
	}
	return files.back();
}
