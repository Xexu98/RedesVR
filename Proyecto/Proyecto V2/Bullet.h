#ifndef BULLET_H
#define BULLET_H

#include "GameObject.h"

class Bullet:public GameObject
{
    private:
    
    double timer;

    public:
    Bullet(SDL_Renderer *renderer = NULL, std::string filename = "", const Vector2D &pos = Vector2D(),
           const Vector2D &rotation = Vector2D(), const Vector2D &size = Vector2D(), int width = 0);

    virtual void update(double deltaTime);
    virtual void handleInput(Input input);

}