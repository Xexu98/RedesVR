#include "Game.h"
#include "Player.h"

#include <algorithm>

Game::Game() : Serializable(), startX(std::vector<double>()), players(std::vector<Player *>()),
               winner(0), nPlayers(2), renderer(nullptr), startY(INITIAL_RESOLUTION_Y - 100), playerFilename("")
{
    Track::setObstaclesPosition(INITIAL_RESOLUTION_X / nPlayers, startY);
    start();
}

Game::Game(SDL_Renderer *r) : Serializable(), startX(std::vector<double>()), players(std::vector<Player *>()),
                              winner(0), nPlayers(2), renderer(r), startY(INITIAL_RESOLUTION_Y - 100), playerFilename("") {}

Game::~Game()
{
    clearPlayers();
}

void Game::to_bin()
{
    int dataSize = 0;
    for (Player *player : players)
    {
        if (player != nullptr)
        {
            player->to_bin();
            dataSize += player->size();
        }
    }


    alloc_data(dataSize + sizeof(int));

    char *aux = _data;

    nPlayers = players.size();
    memcpy(aux, &nPlayers, sizeof(int));
    aux += sizeof(int);

    for (Player *player : players)
    {
        if (player != nullptr)
        {
            Vector2 pos = player->getPosition();
            memcpy(aux, player->data(), player->size());
            aux += player->size();
        }
    }

}

int Game::from_bin(char *data)
{
    try
    {
        clearPlayers();

        char *aux = data;
        memcpy(&nPlayers, aux, sizeof(int));
        aux += sizeof(int);

        //Reconstruir la clase usando el buffer data
        for (int i = 0; i < nPlayers; i++)
        {
            Player *player = new Player(renderer, playerFilename);
            if (player != nullptr)
            {
                player->from_bin(aux);
                aux += player->size();
                players.push_back(player);
            }
        }

        return 0;
    }
    catch (std::exception e)
    {
        return -1;
    }
}

void Game::start()
{
    for (int i = 0; i < nPlayers; i++)
    {
        startX.push_back(i * INITIAL_RESOLUTION_X / nPlayers);
        players.push_back(new Player(renderer, playerFilename, {startX[i], startY}, {}, {0.05, 0.05}, INITIAL_RESOLUTION_X / nPlayers));
       
    }
}

void Game::update(double deltaTime)
{
    for (Player *player : players)
        if (player != nullptr)
            player->update(deltaTime);

    
}

void Game::render()
{
    for (Player *player : players)
        if (player != nullptr)
            player->render();

    for (Track *track : tracks)
        if (track != nullptr)
            track->render();
}

void Game::handleInput(std::vector<Input> input)
{
    for (int i = 0; i < players.size() && i < input.size(); i++)
        if (players[i] != nullptr)
            players[i]->handleInput(input[i]);
}




void Game::removePlayer(Player *player)
{
    auto it = std::find(players.begin(), players.end(), player);
    if (it != players.end())
    {
        players.erase(it);
        if (player != nullptr)
            delete player;
    }
}


void Game::clearPlayers()
{
    //Vector auxiliar para poder borrar referencias
    std::vector<Player *> aux = players;
    for (Player *player : aux)
        removePlayer(player);

    aux.clear();
    players.clear();
}