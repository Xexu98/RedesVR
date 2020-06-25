#include "Player.h"
#include "Game.h"

Player::Player(SDL_Renderer *renderer, std::string filename, const Vector2 &pos, const double &rot, const Vector2 &size, int width)
	: GameObject(renderer, filename, pos, rot, size), lane(N_LANES / 2), velocity(200), slowed(false),
	timer(0), slowTime(1.5), laneWidth(width / N_LANES)
{
	position.x += lane * laneWidth + laneWidth / 4;
}

void Player::update(double deltaTime)
{	
		int x, y;
		SDL_GetMouseState(&x, &y);
		float angle = -90 + (atan2((c->getPosition().getY() - y), (c->getPosition().getX() - x))*180.0000) / 3.1416;
		if (angle >= 0)
		{
			rotation = angle+360;
		}
		else
		{
			rotation = angle;
		}
}

void Player::handleInput(Input input)
{
	switch (input)
	{
	case LEFT:
		moveLane(Vector2D(0,-1));
		break;
	case RIGHT:
		moveLane(Vector2D(0, -1));
		break;
	case UP:
		moveLane(Vector2D(1, 0));
		break;
	case DOWN:
		moveLane(Vector2D(-1, 0));
		break;
	default:
		break;
	}
}

void Player::move(Vector2D dir)
{
	
		position += dir * velocity;
	
}

void Player::lessLife()
{
	if (!hit)
	{
		life = life - 20;
	}
}

void Player::setVelocity(double v)
{
	velocity = v;
}

double Player::getVelocity() const
{
	return velocity;
}
