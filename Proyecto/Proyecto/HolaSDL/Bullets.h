#pragma once
#include "GameObjectPool.h"
#include "Bullet.h"

#include "NaturalMovePC.h"
#include "ImageGC.h"
#include "DeactivateOnBorderExit.h"


class Bullets:public GameObjectPool<Bullet,10>
{
public:
	Bullets(SDLGame* game);
	virtual ~Bullets();
	//void creaPrueba();
	virtual void receive(const void* senderObj, const msg::Message& msg);
	int allBulletsOut();
private:
	NaturalMovePC naturalMove_;
	DeactivateOnBorderExit deactivate_;
	ImageGC bulletImage_;
};

