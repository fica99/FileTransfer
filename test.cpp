#include "Socket.h"
#include "AddrInfo.h"
#include <iostream>

using namespace	std;

int main(void) {
	try {
		AddrInfo	info(NULL, "10000", SOCK_DGRAM);

		cout << "AddrInfo - " << info.getAddrInfo()->ai_addr << endl;
		Socket		sock(move(info));

		cout << "Socket fd - " << sock.getSocketFd() << endl;
		cout << "Info - " << sock.getSocketInfo()->ai_addr << endl;
	} catch (exception &e) {
		cerr << "Exception failed: " << e.what() << endl;
	}
	return 0;
}
