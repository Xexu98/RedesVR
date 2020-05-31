#pragma once
#include <vector>
#include "PhysicsComponent.h"
#include "BlackHole.h"
#include "Bullet.h"
#include "Collisions.h"


class GameManager;
class BulletBlackHoleCollision :public PhysicsComponent
{
public:
	BulletBlackHoleCollision(GameManager* g);
	virtual ~BulletBlackHoleCollision();
	virtual void update(Container* c, Uint32 time);
	virtual void receive(Container* c, const msg::Message& msg);

private:
	const vector<BlackHole*>* blackholes_ = nullptr;
	const vector<Bullet*>* bullets_ = nullptr;
	GameManager* gameMgr_;
};

