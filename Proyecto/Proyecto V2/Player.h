#ifndef PLAYER_H
#define PLAYER_H

#include "GameObject.h"

class Player : public GameObject
{
private:
    int lane;
  

    double velocity;
    double timer;


    void moveLane(int dir);

public:
    Player(SDL_Renderer *renderer = NULL, std::string filename = "", const Vector2 &pos = Vector2(),
           const Vector2 &rotation = Vector2(), const Vector2 &size = Vector2(), int width = 0);

    virtual void update(double deltaTime);
    virtual void handleInput(Input input);

    void slowDown();
    double getVelocity() const;
};

#endif