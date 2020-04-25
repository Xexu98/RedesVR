#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>

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
int main(int argc, char** argv){

    struct addrinfo hints;
    struct addrinfo *res;
    
    memset((void*)&hints, 0, sizeof(struct addrinfo));

    hints.ai_family = AF_UNSPEC;
   

    int rc = getaddrinfo(argv[1], argv[2], &hints, &res);

    if(rc != 0){
        std::cout << "Error getaddrinfo: " << gai_strerror(rc) << std::endl;
        return -1;
    }

    for(struct addrinfo * resaux=res; resaux!=0;resaux = resaux->ai_next){
        char host[NI_MAXHOST];
        char serv[NI_MAXSERV];

        getnameinfo(resaux->ai_addr, resaux->ai_addrlen, host, NI_MAXHOST, serv, NI_MAXSERV, 
        NI_NUMERICHOST | NI_NUMERICSERV);

        std::cout << "Host: " << host << "\tPuerto: " << serv <<"\n";
    }
    freeaddrinfo(res);

    return 0;
}