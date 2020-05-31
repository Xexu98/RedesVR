#pragma once
#include <vector>
#include "PhysicsComponent.h"
#include "BlackHole.h"
#include "Collisions.h"
class GameManager;
class FighterBlackHoleCollision :public PhysicsComponent
{
public:
	FighterBlackHoleCollision(GameManager* g);
	virtual ~FighterBlackHoleCollision();
	virtual void update(Container* c, Uint32 time);
	virtual void receive(Container* c, const msg::Message& msg);
	const vector<BlackHole*>*blackhs_ = nullptr;
	GameObject* fighter_ = nullptr;
	GameManager* gameMgr_;
};

