#pragma once
#include <vector>
#include "PhysicsComponent.h"
#include "Asteroid.h"
#include "BlackHole.h"
#include "Collisions.h"


class GameManager;
class AsteroidBlackHoleCollision:public PhysicsComponent
{
public:
	AsteroidBlackHoleCollision(GameManager* g);
	virtual ~AsteroidBlackHoleCollision();
	virtual void update(Container* c, Uint32 time);
	virtual void receive(Container* c, const msg::Message& msg);

private:
	const vector<Asteroid*>* asteroids_ = nullptr;
	const vector<BlackHole*>* blackholes_ = nullptr;
	GameManager* gameMgr_;
};

