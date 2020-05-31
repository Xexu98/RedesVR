#pragma once
#include <vector>
#include "PhysicsComponent.h"
#include "Player2.h"
#include "Bullet.h"
#include "Collisions.h"

class GameManager;
class BulletPlayer2Collision :public PhysicsComponent
{
public:
	BulletPlayer2Collision(GameManager* g);
	virtual ~BulletPlayer2Collision();
	virtual void update(Container* c, Uint32 time);
	virtual void receive(Container* c, const msg::Message& msg);

private:
	GameObject* player2_ = nullptr;
	const vector<Bullet*>* bullets_ = nullptr;
	GameManager* gameMgr_;
};

