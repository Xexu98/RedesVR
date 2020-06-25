#include "Bullet.h"



Bullet::Bullet(SDL_Renderer *renderer, std::string filename, const Vector2D &pos, const Vector2D &rot, const Vector2D &size, int width)
    : GameObject(renderer, filename, pos, rot, size), lane(N_LANES / 2), velocity(500), slowed(false), timer(0), slowTime(2.0)
{
}

void Bullet::update(double deltaTime)
{
   
}

void Bullet::handleInput(Input input)
{
   
}