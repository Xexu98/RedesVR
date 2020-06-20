#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <vector>

#include "GameObject.h"

class Player;

const int N_LANES = 5;
const int INITIAL_RESOLUTION_X = 1024;
const int INITIAL_RESOLUTION_Y = 720;

class Game : public Serializable
{
private:
    double startY;
    double endY;

    std::vector<double> startX;

    std::vector<Player *> players;

    int nPlayers;
    int winner;

    std::string playerFilename;

    SDL_Renderer *renderer;

public:
    Game();
    Game(SDL_Renderer *r);
    ~Game();

    virtual void to_bin();
    virtual int from_bin(char *data);

    void start();
    void update(double deltaTime);
    void render();
    void handleInput(const std::vector<Input>);

    bool collisionWithObstacle(GameObject *obj);
    

    void removeTrack(Track *track);
    void removePlayer(Player *player);

    void clearPlayers();
};

#endif