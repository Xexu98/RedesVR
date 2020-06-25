#ifndef PLAYER_H
#define PLAYER_H

#include "GameObject.h"

class Player : public GameObject
{
private:
	int lane;
	bool hit;

	double velocity;
	double timer;
	double life = 100;
	double laneWidth;

	void move(Vector2D dir);

public:
	Player(SDL_Renderer *renderer = NULL, std::string filename = "", const Vector2 &pos = Vector2(),
		const double &rotation = 0, const Vector2 &size = Vector2(), int width = 0);

	virtual void update(double deltaTime);
	virtual void handleInput(Input input);

	void lessLife();

	void setVelocity(double v);
	double getVelocity() const;
};

#endif