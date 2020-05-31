#pragma once
#include "GameObjectPool.h"
#include "BulletP2.h"


#include "NaturalMovePC.h"
#include "ImageGC.h"
#include "DeactivateOnBorderExit.h"

class BulletsP2:public GameObjectPool<BulletP2, 10>
{
public:
	BulletsP2(SDLGame* game);
	virtual ~BulletsP2();
	virtual void receive(const void* senderObj, const msg::Message& msg);
	int allBulletsOut();
private:
	NaturalMovePC naturalMove_;
	DeactivateOnBorderExit deactivate_;
	ImageGC bulletImage_;
};

