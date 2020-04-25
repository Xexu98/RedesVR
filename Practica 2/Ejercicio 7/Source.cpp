#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>

#include <iostream>

/*
argv[0] ---> nombre del programa
argv[1] ---> primer argumento (char *)

./addrinfo www.ucm.es 80
argv[0] = "./addrinfo"
argv[1] = "www.ucm.es"
argv[2] = "80"
|
|
V
res->ai_addr ---> (socket + bind)
|
|
V
host (numeric)

./addrinfo 127.0.0.1 80
./addrinfo www.ucm.es http
*/
int main(int argc, char **argv)
{
	
	struct addrinfo hints;
	struct addrinfo * res;

	char buffer[80];
	// ---------------------------------------------------------------------- //
	// INICIALIZACI�N SOCKET & BIND //
	// ---------------------------------------------------------------------- //

	memset(&hints, 0, sizeof(struct addrinfo));

	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_DGRAM;

	int rc = getaddrinfo(argv[1], argv[2], &hints, &res);

	if (rc != 0)
	{
		std::cerr << "getaddrinfo: " << gai_strerror(rc) << std::endl;
		return -1;
	}


	struct sockaddr client_addr;
	socklen_t client_len = sizeof(struct sockaddr);

	// res contiene la representaci�n como sockaddr de direcci�n + puerto

	int sd = socket(res->ai_family, res->ai_socktype, 0);

	sendto(sd, argv[3], sizeof(argv[3]), 0, res->ai_addr, res->ai_addrlen);

	ssize_t bytes = recvfrom(sd,(void*)buffer, 79 * sizeof(char), 0, res->ai_addr,
		&res->ai_addrlen);

	buffer[bytes]='\0';
	
	std::cout<<buffer<<std::endl;


	freeaddrinfo(res);
	

	return 0;
}