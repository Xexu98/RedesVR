#include "ClientMessage.h"

ClientMessage::ClientMessage() {}

ClientMessage::ClientMessage(const std::string &n, const std::string &m) : nick(n), message(m) {}

void ClientMessage::to_bin()
{
    
    alloc_data(MESSAGE_SIZE);

    memset(_data, 0, MESSAGE_SIZE);

    memcpy(_data, static_cast<void *>(&type), sizeof(uint8_t));
    char *aux = _data + sizeof(uint8_t);
    memcpy(aux, nick.c_str(), 8);
    aux += 8;
    memcpy(aux, message.c_str(), 80);
}

int ClientMessage::from_bin(char *bobj)
{
    try
    {
        alloc_data(MESSAGE_SIZE);

        memcpy(static_cast<void *>(_data), bobj, MESSAGE_SIZE);

        memcpy(static_cast<void *>(&type), _data, sizeof(uint8_t));
        char *aux = _data + sizeof(uint8_t);

        char name[8];
        memcpy(name, aux, 8);
        nick = name;
        aux += 8;

        char msg[80];
        memcpy(msg, aux, 80);
        message = msg;

        return 0;
    }
    catch (std::exception e)
    {
        return -1;
    }
}