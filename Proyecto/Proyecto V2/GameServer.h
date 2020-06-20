#ifndef GAME_SERVER_H
#define GAME_SERVER_H

#include <unistd.h>
#include <string.h>
#include <vector>
#include <mutex>
#include <thread>

#include "Socket.h"
#include "ClientMessage.h"
#include "Game.h"


class GameServer
{
public:
    GameServer(const char *s, const char *p);

    
    void serverThread();

    
    void simulationThread();
    void sendGameState();

    bool processFound(Socket *socket, ClientMessage &msg);
    void processNotFound(Socket *socket, ClientMessage &msg);

    void checkStart();

private:
  
    std::pair<Socket *, Socket *> clients;

    std::mutex stateLock;

    Game *state;

    Socket socket;

    bool end;
};

#endif