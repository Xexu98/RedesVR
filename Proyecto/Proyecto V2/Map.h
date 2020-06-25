#ifndef TRACK_H
#define TRACK_H

#include "GameObject.h"

#include <vector>

class Player;
class Bullet;

const int MIN_O_DIST = 50;
const int MAX_O_DIST = 100;

class Map : public Serializable
{
private:
    static std::vector<Vector2D> obstaclesBasePos;
    static double endY;

    std::vector<Bullet *> bullets;

    Player *player;
	Bullet *bullet;
    GameObject *background;

    std::string bulletFilename;
    std::string playerFilename;
    std::string backgroundFilename;
  

    int offset;
    Vector2D startPos;

    SDL_Renderer *renderer;

public:
    Map(SDL_Renderer *renderer, const Vector2D &startPos = Vector2D(), int width = 0);
    ~Map();

    virtual void to_bin();
    virtual int from_bin(char *data);

    void update(double deltaTime);
    void render();
    void handleInput(Input input);

    void createBullets();
    void checkCollisions();

    static void setBulletsPosition(int width, int posY);

    bool raceEnded();

    void removeBullet(Bullet *obstacle);
    void clearBullets();
};

#endif