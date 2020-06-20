#ifndef BULLET_H
#define BULLET_H

#include "GameObject.h"

class Bullet:public GameObject
{
    private:
    
    double timer;

    public:
    Bullet(SDL_Renderer *renderer = NULL, std::string filename = "", const Vector2 &pos = Vector2(),
           const Vector2 &rotation = Vector2(), const Vector2 &size = Vector2(), int width = 0);

    virtual void update(double deltaTime);
    virtual void handleInput(Input input);
}