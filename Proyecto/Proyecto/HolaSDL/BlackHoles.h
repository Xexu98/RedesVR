#pragma once
#include "GameObjectPool.h"
#include "BlackHole.h"
#include "NaturalMovePC.h"
#include "ImageGC.h"
#include "RotatingPC.h"

class BlackHoles:public GameObjectPool<BlackHole,8>
{
public:
	BlackHoles(SDLGame* game);
	virtual ~BlackHoles();
	virtual void receive(const void* senderObj, const msg::Message& msg);
	

private:
	ImageGC blackHoleImg_;
	NaturalMovePC naturalMove_;
	RotatingPC rotating_;
	void colocaBlackHole();

	int numgen = 1;
};

