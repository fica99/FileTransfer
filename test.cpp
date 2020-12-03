#include "Socket.h"
#include "AddrInfo.h"
#include "Bind.h"
#include <iostream>

using namespace	std;

int main(void) {
	AddrInfo	info(NULL, "8", SOCK_DGRAM);

	cout << "AddrInfo - " << info.getAddrInfo()->ai_addr << endl;
	Socket		sock(move(info));

	cout << "Socket fd - " << sock.getSocketFd() << endl;
	cout << "Info - " << sock.getSocketInfo()->ai_addr << endl;

	Bind{sock};

	return 0;
}
