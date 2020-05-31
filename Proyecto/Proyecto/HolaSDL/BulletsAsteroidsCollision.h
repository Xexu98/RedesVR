#pragma once
#include <vector>
#include "PhysicsComponent.h"
#include "Asteroid.h"
#include "Bullet.h"
#include "Collisions.h"

class GameManager;
class BulletsAsteroidsCollision:public PhysicsComponent
{
public:
	BulletsAsteroidsCollision(GameManager* g);
	virtual ~BulletsAsteroidsCollision();
	virtual void update(Container* c, Uint32 time);
	virtual void receive(Container* c, const msg::Message& msg);

private:
	const vector<Asteroid*>* asteroids_ = nullptr;
	const vector<Bullet*>* bullets_ = nullptr;
	GameManager* gameMgr_;
};

