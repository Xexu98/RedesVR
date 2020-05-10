#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>

#include <iostream>
#include <pthread.h>
/*
./tcp 0.0.0.0 7777
*/




class MessageThread
{
private:

    char buffer[80];
    ssize_t bytes;
    int sd_client;

public:

    MessageThread(int sd):sd_client(sd){}
    
    void do_message()
    {
        while (true)
        {
            struct sockaddr client_addr;
            socklen_t client_len = sizeof(struct sockaddr);
            bytes = recv(sd_client, (void *) buffer, sizeof(char)*79, 0);

            if (bytes <= 0)
            {
                break;
            }
            

            sendto(sd_client, buffer,bytes, 0,&client_addr,client_len);
        }
          std::cout << "CONEXION FINISHED " << std::endl;
    }
    

};


int main(int argc, char **argv)
{
struct addrinfo hints;
struct addrinfo * res;

// ---------------------------------------------------------------------- //
// INICIALIZACIÓN SOCKET & BIND //
// ---------------------------------------------------------------------- //

memset(&hints, 0, sizeof(struct addrinfo));

hints.ai_family = AF_INET;
hints.ai_socktype = SOCK_STREAM;

int rc = getaddrinfo(argv[1], argv[2], &hints, &res);

if ( rc != 0 )
{
std::cerr << "getaddrinfo: " << gai_strerror(rc) << std::endl;
return -1;
}

// res contiene la representación como sockaddr de dirección + puerto

int sd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);

bind(sd, res->ai_addr, res->ai_addrlen);


freeaddrinfo(res);

// ---------------------------------------------------------------------- //
// PUBLICAR EL SERVIDOR (LISTEN) //
// ---------------------------------------------------------------------- //
listen(sd, 16);

// ---------------------------------------------------------------------- //
// GESTION DE LAS CONEXIONES AL SERVIDOR //
// ---------------------------------------------------------------------- //
while (true)
{
   
    char host[NI_MAXHOST];
    char service[NI_MAXSERV];

    struct sockaddr client_addr;
    socklen_t client_len = sizeof(struct sockaddr);

    int sd_client = accept(sd, &client_addr, &client_len);

    getnameinfo(&client_addr, client_len, host, NI_MAXHOST, service,
    NI_MAXSERV, NI_NUMERICHOST | NI_NUMERICSERV);

    std::cout << "CONEXION DESDE IP: " << host << " PUERTO: " << service
    << std::endl;

    MessageThread* mt = new MessageThread(sd_client);
    pthread_attr_t attr;
    pthread_attr_init (&attr);
    pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_DETACHED);
    pthread_t thread;
    pthread_create(&thread,& attr,do_message,mt);
}
return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>

#include <iostream>
#include <thread>
#include <vector>

/*
./tcp 0.0.0.0 7777

class ConexionTCP
{
public:


private:


};
*/
class ConexionThread {
private:
	char buffer[80];
	ssize_t bytes;
	int sd_client;
public:
	ConexionThread(int sd_) :sd(sd_) {}
	void haz_conexion()
	{
		// ---------------------------------------------------------------------- //
		// GESTION DE LA CONEXION CLIENTE //
		// ---------------------------------------------------------------------- //
		while (true)
		{
			struct sockaddr src_addr;
			socklen_t addrlen = sizeof(struct sockaddr);

			bytes = recv(sd, (void *)buffer, sizeof(char) * 79, 0);

			if (bytes <= 0)break;
			buffer[bytes] = '\0';

			std::cout << "THREAD: " << pthread_self() << " MESSAGE: " << buffer << std::endl;

			sendto(sd_cliente, buffer, bytes, 0, &src_addr, addrlen); 
		}	

		std::cout << "CONEXIÓN TERMINADA" << std::endl;

		}
	}
};

extern "C" void* _haz_conexion(void* ct_)
{
	ConnectionThread* ct = static_cast<ConnectionThread*>(ct_);
	ct->haz_conexion();
	delete ct;
	return 0;
}

int main(int argc, char **argv)
{
	struct addrinfo hints;
	struct addrinfo * res;

	// ---------------------------------------------------------------------- //
	// INICIALIZACIÓN SOCKET & BIND //
	// ---------------------------------------------------------------------- //

	memset(&hints, 0, sizeof(struct addrinfo));

	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;

	int rc = getaddrinfo(argv[1], argv[2], &hints, &res);

	if (rc != 0)
	{
		std::cerr << "getaddrinfo: " << gai_strerror(rc) << std::endl;
		return -1;
	}

	// res contiene la representación como sockaddr de dirección + puerto

	int sd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);

	bind(sd, res->ai_addr, res->ai_addrlen);


	freeaddrinfo(res);

	// ---------------------------------------------------------------------- //
	// PUBLICAR EL SERVIDOR (LISTEN) //
	// ---------------------------------------------------------------------- //
	listen(sd, 16);

	// ---------------------------------------------------------------------- //
	// GESTION DE LAS CONEXIONES AL SERVIDOR //
	// ---------------------------------------------------------------------- //
	while (true)
	{

		char host[NI_MAXHOST];
		char service[NI_MAXSERV];

		struct sockaddr client_addr;
		socklen_t client_len = sizeof(struct sockaddr);

		int sd_client = accept(sd, &client_addr, &client_len);

		getnameinfo(&client_addr, client_len, host, NI_MAXHOST, service,
			NI_MAXSERV, NI_NUMERICHOST | NI_NUMERICSERV);

		std::cout << "CONEXION DESDE IP: " << host << " PUERTO: " << service
			<< std::endl;

		ConexionThread* ct = new ConexionThread(sd_client);
		pthread_attr_t attr;
		pthread_attr_init(&attr);
		pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
		pthread_t thread;
		pthread_create(&thread, &attr, _haz_conexion, ct);
	}
	return 0;
}