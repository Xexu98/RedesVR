#pragma once
#include "PhysicsComponent.h"
#include "Player.h"
#include "BulletP2.h"
#include "Collisions.h"

class GameManager;
class BulletsP2PlayerCollision :public PhysicsComponent
{
public:
	BulletsP2PlayerCollision(GameManager* g);
	virtual ~BulletsP2PlayerCollision();
	virtual void update(Container* c, Uint32 time);
	virtual void receive(Container* c, const msg::Message& msg);

private:
	GameObject* player_ = nullptr;
	const vector<BulletP2*>* bulletsp2_ = nullptr;
	GameManager* gameMgr_;
};

