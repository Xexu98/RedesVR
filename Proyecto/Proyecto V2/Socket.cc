#include <string.h>

#include "Serializable.h"
#include "Socket.h"

Socket::Socket(const char *address, const char *port) : sd(-1)
{
    
    struct addrinfo hints;
    struct addrinfo *res;

    memset(&hints, 0, sizeof(struct addrinfo));

    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_DGRAM;

    int rc = getaddrinfo(address, port, &hints, &res);
    if (rc != 0)
        std::cerr << "getaddrinfo: " << gai_strerror(rc) << std::endl;

    sa = *res->ai_addr;
    sa_len = res->ai_addrlen;
    sd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);

    freeaddrinfo(res);
}

int Socket::recv(Serializable &obj, Socket *&sock)
{
    struct sockaddr sa;
    socklen_t sa_len = sizeof(struct sockaddr);

    char buffer[MAX_MESSAGE_SIZE];
    memset(buffer, '\0', MAX_MESSAGE_SIZE);

    ssize_t bytes = recvfrom(sd, buffer, MAX_MESSAGE_SIZE, 0, &sa, &sa_len);

    if (bytes <= 0)
        return -1;

    if (sock != 0)
        sock = new Socket(&sa, sa_len);

    obj.from_bin(buffer);

    return 0;
}

int Socket::send(Serializable &obj, const Socket &sock)
{
    int sd = sock.sd;
    if (sd == -1)
    {
        sockaddr_in *aux = (sockaddr_in *)&sock.sa;
        sd = socket(aux->sin_family, SOCK_DGRAM, 0);
    }

    
    obj.to_bin();

    sendto(sd, obj.data(), obj.size(), 0, &sock.sa, sock.sa_len);
}

bool operator==(const Socket &s1, const Socket &s2)
{
   
    sockaddr_in *sa1 = (sockaddr_in *)&s1.sa;
    sockaddr_in *sa2 = (sockaddr_in *)&s2.sa;

    return sa1->sin_family == sa2->sin_family &&
           sa1->sin_port == sa2->sin_port &&
           sa1->sin_addr.s_addr == sa2->sin_addr.s_addr;
};

bool operator!=(const Socket &s1, const Socket &s2)
{
    return !(s1 == s2);
}

std::ostream &operator<<(std::ostream &os, const Socket &s)
{
    char host[NI_MAXHOST];
    char serv[NI_MAXSERV];

    getnameinfo((struct sockaddr *)&(s.sa), s.sa_len, host, NI_MAXHOST, serv, NI_MAXSERV, NI_NUMERICHOST);

    os << host << ":" << serv;

    return os;
};