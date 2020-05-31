#pragma once
#include "Container.h"

class Bullet:public Container
{
public:
	Bullet();
	virtual ~Bullet();
	virtual void receive(const void* senderObj, const msg::Message& msg) {};
};

