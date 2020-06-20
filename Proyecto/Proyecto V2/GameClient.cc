#include "GameClient.h"
#include "ClientMessage.h"

#include <string>
#include <unistd.h>
#include <string.h>

#include <stdio.h>

GameClient::GameClient(const char *s, const char *p, const char *n) : socket(s, p), nick(n), window(NULL), renderer(NULL), quit(false)
{
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_EVENTS);

    SDL_DisplayMode monitor;
    SDL_GetCurrentDisplayMode(0, &monitor);

    window = SDL_CreateWindow("Drifting in the 20s", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, INITIAL_RESOLUTION_X, INITIAL_RESOLUTION_Y,
                              SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    game = new Game(renderer);
}

void GameClient::login()
{
    std::string msg;

    ClientMessage em(nick, msg);
    em.type = ClientMessage::LOGIN;

    socket.send(em, socket);
}

void GameClient::logout()
{
    std::string msg;

    ClientMessage em(nick, msg);
    em.type = ClientMessage::LOGOUT;

    socket.send(em, socket);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void GameClient::input_thread()
{
    while (!quit)
        handleEvents();

    logout();
}

void GameClient::net_thread()
{
    int i = 0;
    while (!quit)
    {
        socket.recv(*game);
        std::cout << "Render " << i++ << "\n";
        render();
    }
}

void GameClient::render()
{
    SDL_RenderClear(renderer);

    if (game != nullptr)
        game->render();

    SDL_RenderPresent(renderer);
}

void GameClient::handleEvents()
{
    SDL_Event event;
    while (SDL_PollEvent(&event) && !quit)
    {
        if (event.type == SDL_QUIT)
            quit = true;
        else if (event.type == SDL_WINDOWEVENT)
        {
            if (event.window.event == SDL_WINDOWEVENT_RESIZED)
                SDL_RenderSetScale(renderer, event.window.data1 / (float)INITIAL_RESOLUTION_X, event.window.data2 / (float)INITIAL_RESOLUTION_Y);
        }
        else if (event.type == SDL_KEYDOWN)
        {
            std::string msg;
            ClientMessage em;

            if (event.key.keysym.sym == SDLK_LEFT)
            {
                msg = "LEFT";

                em = ClientMessage(nick, msg);
                em.type = ClientMessage::INPUT;

                socket.send(em, socket);
            }
            else if (event.key.keysym.sym == SDLK_RIGHT)
            {
                msg = "RIGHT";

                em = ClientMessage(nick, msg);
                em.type = ClientMessage::INPUT;

                socket.send(em, socket);
            }
        }
    }
}