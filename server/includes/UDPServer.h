#pragma once

class UDPServer {
public:
	UDPServer(void);
	~UDPServer(void);
private:
	int	socket_fd;
};
