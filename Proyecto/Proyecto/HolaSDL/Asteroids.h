#pragma once
#include "GameObjectPool.h"
#include "Asteroid.h"

#include "ImageGC.h"
#include "NaturalMovePC.h"
#include "ShowUpAtOppositeSidePC.h"
#include "RotatingPC.h"

class Asteroids : public GameObjectPool <Asteroid,50>
{
public:
	Asteroids(SDLGame* game);
	virtual ~Asteroids();
	// ...
	int getGeneration() { return generations_; };
	void setGeneration(int g) { generations_ = g; };
	virtual void receive(const void* senderObj, const msg::Message& msg);
	void colocaAsteroides(int numast);
	int aliveAsteroids();
private:
	// ...
	int generations_;
	//component for Asteroid
	ImageGC asteroidImage_;
	NaturalMovePC naturalMove_;
	RotatingPC rotating_;
	ShowUpAtOppositeSidePC showUpAtOppositeSide_;

	
};

