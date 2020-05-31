#pragma once
#include <vector>
#include "PhysicsComponent.h"
#include "Asteroid.h"
#include "Collisions.h"

class GameManager;
class FighterAsteroidCollision:public PhysicsComponent
{
public:
	FighterAsteroidCollision(GameManager* g);
	virtual ~FighterAsteroidCollision();
	virtual void update(Container* c, Uint32 time);

	GameObject* fighter_=nullptr;
	const vector<Asteroid*>* asteroids_= nullptr;
	//este metodo debe ser heredeado de la clase padre de component
	virtual void receive(Container* c, const msg::Message& msg);

	GameManager* gameMgr_;
};

