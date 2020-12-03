#include "Error.h"

using namespace	std;

Error::Error(const char *msg) {
	if (errno)
		perror(msg);
	else
		cerr << msg << endl;
	exit(EXIT_FAILURE);
}

Error::Error(const string &msg) {
	Error(msg.c_str());
}
