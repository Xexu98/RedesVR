#include "GameServer.h"

#include <iostream>
#include <memory>
#include <chrono>

using timer = std::chrono::high_resolution_clock;
using timePoint = timer::time_point;
using ms = std::chrono::duration<double, std::milli>;

GameServer::GameServer(const char *s, const char *p) : socket(s, p), clients({nullptr, nullptr}), state(nullptr), end(false)
{
    socket.bind();
}

void GameServer::serverThread()
{
    while (!end)
    {
        ClientMessage msg;
        Socket *s = &socket;
        socket.recv(msg, s);

        if (s == nullptr || s == &socket)
            continue;

        if (!processFound(s, msg))
            processNotFound(s, msg);
    }
}

void GameServer::simulationThread()
{
    state = new Game();

    timePoint last;
    timePoint current = timer::now();
    double deltaTime = 0.0;
    int i = 0;
    while (state != nullptr && !state->raceEnded() && clients.first != nullptr && clients.second != nullptr)
    {
        last = current;
        current = timer::now();
        deltaTime = ms(current - last).count() / 1000.0;

        stateLock.lock();
        state->update(deltaTime);
        std::cout << "Update " << i++ << " " << deltaTime << "\n";
        sendGameState();
        stateLock.unlock();
        std::this_thread::sleep_for(std::chrono::milliseconds(150));
    }
    end = true;
    std::cout << "Fin\n";
}

void GameServer::sendGameState()
{
    if (clients.first != nullptr)
        socket.send(*state, *clients.first);
    if (clients.second != nullptr)
        socket.send(*state, *clients.second);
}

bool GameServer::processFound(Socket *socket, ClientMessage &msg)
{
    bool foundFirst = clients.first != nullptr && (*socket == *(clients.first));
    bool foundSecond = clients.second != nullptr && (*socket == *(clients.second));

    if (foundFirst || foundSecond)
    {
        std::cout << "FOUND\n";
        if (msg.type == ClientMessage::LOGOUT)
        {
            if (foundFirst)
                clients.first = nullptr;
            else
                clients.second = nullptr;
        }
        else if (msg.type == ClientMessage::INPUT && state != nullptr)
        {
            Input input = (msg.message == "LEFT") ? Input::LEFT : (msg.message == "RIGHT") ? Input::RIGHT : Input::NONE;

           
            stateLock.lock();
            if (foundFirst)
                state->handleInput({input, Input::NONE});
            else
                state->handleInput({Input::NONE, input});
            stateLock.unlock();
        }
        return true;
    }
    else
        return false;
}

void GameServer::processNotFound(Socket *socket, ClientMessage &msg)
{
    std::cout << "NOT FOUND\n";
    if (msg.type == ClientMessage::LOGIN)
    {
        if (clients.first == nullptr)
        {
            clients.first = socket;
            checkStart();
            std::cout << "Client " << msg.nick << " Logged in as player1\n";
        }
        else if (clients.second == nullptr)
        {
            clients.second = socket;
            checkStart();
            std::cout << "Client " << msg.nick << " Logged in as player2\n";
        }
        else
        {
            std::cout << "Client " << msg.nick << " not Logged in, match is full\n";
            if (socket != nullptr)
                delete socket;

            return;
        }
    }
    else if (socket != nullptr)
        delete socket;
}

void GameServer::checkStart()
{
    if (clients.first != nullptr && clients.second != nullptr)
    {
        std::thread hilo(&GameServer::simulationThread, this);
        hilo.detach();
    }
}