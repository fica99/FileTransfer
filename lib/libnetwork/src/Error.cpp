#include "Error.h"

using namespace	std;

void Error::error(const char *msg) {
	if (errno)
		perror(msg);
	else
		cerr << msg << endl;
	exit(EXIT_FAILURE);
}

void Error::error(const string &msg) {
	error(msg.c_str());
}
