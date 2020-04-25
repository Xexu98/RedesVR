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

	// res contiene la representaci�n como sockaddr de direcci�n + puerto

	int sd = socket(res->ai_family, res->ai_socktype, 0);

	bind(sd, res->ai_addr, res->ai_addrlen);
	
	freeaddrinfo(res);

	// ---------------------------------------------------------------------- //
	// RECEPCI�N MENSAJE DE CLIENTE //
	// ---------------------------------------------------------------------- //

	bool running = true;


	while (running)
	{
		char buffer[80];
		char host[NI_MAXHOST];
		char service[NI_MAXSERV];

		struct sockaddr client_addr;
		socklen_t client_len = sizeof(struct sockaddr);

		ssize_t bytes = recvfrom(sd, buffer, 79 * sizeof(char), 0, &client_addr,
		&client_len);

		getnameinfo(&client_addr, client_len, host, NI_MAXHOST, service,
		NI_MAXSERV, NI_NUMERICHOST | NI_NUMERICSERV);

		time_t t = time(0);

		struct tm* tiempo;

		char bufferT [9];

		if(buffer[0]=='t')
		{
			tiempo=localtime(&t);
			strftime(bufferT,sizeof(bufferT),"%T",tiempo);
			// ---------------------------------------------------------------------- //
			// RESPUESTA AL CLIENTE //
			// ---------------------------------------------------------------------- //
			sendto(sd, buffer, bytes, 0, &client_addr, client_len);
		}
		else if (buffer[0]=='d')
		{
			tiempo=localtime(&t);
			strftime(bufferT,sizeof(bufferT),"%D",tiempo);
			// ---------------------------------------------------------------------- //
			// RESPUESTA AL CLIENTE //
			// ---------------------------------------------------------------------- //
			sendto(sd, buffer, bytes, 0, &client_addr, client_len);
		}
		else if(buffer[0]=='q')
		{
			running=false;	
		}

		std::cout << "IP: " << host << " PUERTO: " << service
		<< "MENSAJE: " << buffer << std::endl;
	}
	

	return 0;
}