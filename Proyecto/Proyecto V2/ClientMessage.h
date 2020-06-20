#ifndef CLIENT_MESSAGE_H
#define CLIENT_MESSAGE_H

#include <string>
#include <string.h>
#include <unistd.h>

#include "Serializable.h"


class ClientMessage : public Serializable
{
public:
    static const size_t MESSAGE_SIZE = sizeof(char) * 88 + sizeof(uint8_t);

    enum MessageType
    {
        LOGIN = 0,
        INPUT = 1,
        LOGOUT = 2
    };

    ClientMessage();

    ClientMessage(const std::string &n, const std::string &m);

    void to_bin();

    int from_bin(char *bobj);

    uint8_t type;
    std::string nick;
    std::string message;
};

#endif