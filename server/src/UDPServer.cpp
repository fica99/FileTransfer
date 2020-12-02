#include "UDPServer.h"

struct addrinfo	*get_addr_info(void)
{
	struct addrinfo	hints;
	struct addrinfo	*serv_info;
	int				rv;

	ft_bzero(&hints, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;
	if ((rv = getaddrinfo(NULL, PORT, &hints, &serv_info)) != 0)
	{
		ft_dprintf(STDERR_FILENO, "getaddrinfo: %s\n", gai_strerror(rv));
		exit(1);
	}
	return (serv_info);
}

//int			get_socket_fd(struct addrinfo *serv_info, struct addrinfo **info)
//{
//	struct addrinfo	*p;
//	int				socket_fd;

//	p = serv_info;
//	while (p)
//	{
//		socket_fd = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
//		if (socket_fd != -1)
//			break ;
//		p = p->ai_next;
//	}
//	if (!p)
//	{
//		ft_dprintf(STDERR_FILENO, "Failed to get socket file descriptor\n");
//		exit(1);
//	}
//	*info = p;
//	return (socket_fd);
//}


//void testing(void){
//	int							rv;
//	struct addrinfo	*info;
//	struct addrinfo	*serv_info;
//	int							fd;

//	serv_info = get_addr_info();
//	fd = get_socket_fd(serv_info, &info);
//	rv = 1;
//	if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &rv, sizeof(int)) == -1)
//		error_message("setsockopt");
//	while (bind(fd, info->ai_addr, info->ai_addrlen) == -1)
//	{
//		close(fd);
//		fd = get_socket_fd(info->ai_next, &info);
//	}
//	freeaddrinfo(serv_info);
//	return (fd);
//}

//void closing(void){
//	if (close(socket_fd) < 0)
//		error_message("Error - close() failed");
//}

UDPServer::UDPServer(void) {

}



UDPServer::~UDPServer(void) {

}
