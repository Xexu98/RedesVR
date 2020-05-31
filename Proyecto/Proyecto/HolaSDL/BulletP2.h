#pragma once
#include "Container.h"

class BulletP2:public Container
{
public:
	BulletP2();
	virtual ~BulletP2();
	virtual void receive(const void* senderObj, const msg::Message& msg) {};

};

