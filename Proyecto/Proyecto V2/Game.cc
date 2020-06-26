#include "Game.h"
#include "Map.h"
#include "Player.h"

#include <algorithm>

Game::Game() : Serializable(), maps(std::vector<Map *>()),
               winner(0), nPlayers(2), renderer(nullptr), startY(INITIAL_RESOLUTION_Y - 100)
{
    Map::setObstaclesPosition(INITIAL_RESOLUTION_X / nPlayers, startY - 50);
    start();
}

Game::Game(SDL_Renderer *r) : Serializable(), maps(std::vector<Map *>()),
                              winner(0), nPlayers(2), renderer(r), startY(INITIAL_RESOLUTION_Y - 100) {}

Game::~Game()
{
    clearMaps();
}

void Game::to_bin()
{
    int dataSize = 0;

    for (Map *map : maps)
    {
        if (map != nullptr)
        {
			map->to_bin();
            dataSize += map->size();
        }
    }

    alloc_data(dataSize + sizeof(int));

    char *aux = _data;

    nPlayers = maps.size();
    memcpy(aux, &nPlayers, sizeof(int));
    aux += sizeof(int);

    for (Map *map : maps)
    {
        if (map != nullptr)
        {
            memcpy(aux, map->data(), map->size());
            aux += map->size();
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

        if (maps.size() < nPlayers)
            for (int i = maps.size(); i < nPlayers; i++)
				maps.push_back(new Map(renderer));

        //Reconstruir la clase usando el buffer data
        for (int i = 0; i < nPlayers; i++)
        {
            Map *map = maps[i];
            if (map != nullptr)
            {
				map->from_bin(aux);
                aux += map->size();
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
		maps.push_back(new Map(renderer, {i * (double)INITIAL_RESOLUTION_X / (double)nPlayers, startY}, INITIAL_RESOLUTION_X / nPlayers));
}

void Game::update(double deltaTime)
{
    for (Map *map : maps)
        if (map != nullptr)
			map->update(deltaTime);
}

void Game::render()
{
    for (Map *map : maps)
        if (map != nullptr)
			map->render();
}

void Game::handleInput(int i, Input input)
{
    if (i < maps.size() && maps[i] != nullptr)
		maps[i]->handleInput(input);
}

bool Game::raceEnded()
{
    int i = 0;
    while (i < maps.size() && winner == 0)
    {
        winner = (maps[i] != nullptr && maps[i]->raceEnded()) ? i+1 : 0;
        i++;
    }

    return winner != 0;
}

void Game::removeMap(Map *map)
{
    auto it = std::find(maps.begin(), maps.end(), map);
    if (it != maps.end())
    {
		maps.erase(it);
        if (map != nullptr)
            delete map;
    }
}

void Game::clearMaps()
{
    //Vector auxiliar para poder borrar referencias
    std::vector<Map *> aux = maps;
    for (Map *map : aux)
        removeMap(map);

    aux.clear();
	maps.clear();
}