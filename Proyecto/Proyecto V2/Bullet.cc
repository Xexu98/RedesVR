#include "Bullet.h"



Bullet::Bullet(SDL_Renderer *renderer, std::string filename, const Vector2 &pos, const Vector2 &rot, const Vector2 &size, int width)
    : GameObject(renderer, filename, pos, rot, size), lane(N_LANES / 2), velocity(5), slowed(false), timer(0), slowTime(2.0)
{
}

void Bullet::update(double deltaTime)
{
    if (slowed)
    {
        timer -= deltaTime;
        if (timer <= 0)
        {

            velocity *= 2;
            timer = 0;
        }
    }
}

void Bullet::handleInput(Input input)
{
   
}