#ifndef GAME_CLIENT_H
#define GAME_CLIENT_H

#include "Socket.h"
#include "Game.h"

//Clase para el cliente del juego
class GameClient
{
public:
    
    GameClient(const char *s, const char *p, const char *n);

    
    void login();

  
    void logout();

    
    void input_thread();

    
    void net_thread();

    void render();
    void handleEvents();

private:
    
    Socket socket;

    
    std::string nick;

    SDL_Window *window;
    SDL_Renderer *renderer;

    bool quit;

    Game *game;
};

#endif