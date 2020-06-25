#include "Game.h"
#include "Map.h"
#include "Player.h"

#include <algorithm>

Game::Game() : Serializable(), tracks(std::vector<Map *>()),
               winner(0), nPlayers(2), renderer(nullptr), startY(INITIAL_RESOLUTION_Y - 100)
{
    Map::setObstaclesPosition(INITIAL_RESOLUTION_X / nPlayers, startY - 50);
    start();
}

Game::Game(SDL_Renderer *r) : Serializable(), tracks(std::vector<Map *>()),
                              winner(0), nPlayers(2), renderer(r), startY(INITIAL_RESOLUTION_Y - 100) {}

Game::~Game()
{
    clearTracks();
}

void Game::to_bin()
{
    int dataSize = 0;

    for (Map *track : tracks)
    {
        if (track != nullptr)
        {
            track->to_bin();
            dataSize += track->size();
        }
    }

    alloc_data(dataSize + sizeof(int));

    char *aux = _data;

    nPlayers = tracks.size();
    memcpy(aux, &nPlayers, sizeof(int));
    aux += sizeof(int);

    for (Map *track : tracks)
    {
        if (track != nullptr)
        {
            memcpy(aux, track->data(), track->size());
            aux += track->size();
        }
    }
}

int Game::from_bin(char *data)
{
    try
    {
        char *aux = data;
        memcpy(&nPlayers, aux, sizeof(int));
        aux += sizeof(int);

        if (tracks.size() < nPlayers)
            for (int i = tracks.size(); i < nPlayers; i++)
                tracks.push_back(new Map(renderer));

        //Reconstruir la clase usando el buffer data
        for (int i = 0; i < nPlayers; i++)
        {
            Map *track = tracks[i];
            if (track != nullptr)
            {
                track->from_bin(aux);
                aux += track->size();
            }
        }

        return 0;
    }
    catch (std::exception e)
    {
        std::cout << "Error al deserializar\n";
        return -1;
    }
}

void Game::start()
{
    for (int i = 0; i < nPlayers; i++)
        tracks.push_back(new Map(renderer, {i * (double)INITIAL_RESOLUTION_X / (double)nPlayers, startY}, INITIAL_RESOLUTION_X / nPlayers));
}

void Game::update(double deltaTime)
{
    for (Map *track : tracks)
        if (track != nullptr)
            track->update(deltaTime);
}

void Game::render()
{
    for (Map *track : tracks)
        if (track != nullptr)
            track->render();
}

void Game::handleInput(int i, Input input)
{
    if (i < tracks.size() && tracks[i] != nullptr)
        tracks[i]->handleInput(input);
}

bool Game::raceEnded()
{
    int i = 0;
    while (i < tracks.size() && winner == 0)
    {
        winner = (tracks[i] != nullptr && tracks[i]->raceEnded()) ? i+1 : 0;
        i++;
    }

    return winner != 0;
}

void Game::removeTrack(Map *track)
{
    auto it = std::find(tracks.begin(), tracks.end(), track);
    if (it != tracks.end())
    {
        tracks.erase(it);
        if (track != nullptr)
            delete track;
    }
}

void Game::clearTracks()
{
    //Vector auxiliar para poder borrar referencias
    std::vector<Map *> aux = tracks;
    for (Map *track : aux)
        removeTrack(track);

    aux.clear();
    tracks.clear();
}