#include "Player.h"
#include "Game.h"

Player::Player(SDL_Renderer *renderer, std::string filename, const Vector2 &pos, const Vector2 &rot, const Vector2 &size, int width)
    : GameObject(renderer, filename, pos, rot, size), lane(N_LANES / 2), velocity(5), slowed(false), timer(0), slowTime(2.0)
{
    position.x += lane * width / N_LANES;
}

void Player::update(double deltaTime)
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

void Player::handleInput(Input input)
{
    switch (input)
    {
    case LEFT:
        moveLane(-1);
        break;
    case RIGHT:
        moveLane(1);
        break;
    default:
        break;
    }
}

void Player::moveLane(int dir)
{
    SDL_DisplayMode monitor;
    SDL_GetCurrentDisplayMode(0, &monitor);
    int window_width = monitor.w;

    int aux = lane + dir;
    if (aux >= 0 && aux < N_LANES)
    {
        lane = aux;
        position.x += dir * N_LANES / window_width;
    }
}

void Player::slowDown()
{
    if (!slowed)
    {
        velocity = velocity / 2;
        slowed = true;
        timer = slowTime;
    }
}

double Player::getVelocity() const
{
    return velocity;
}