#pragma once
#include "Container.h"

class BlackHole:public Container
{
public:
	BlackHole();
	virtual ~BlackHole();
	virtual void receive(const void* senderObj, const msg::Message& msg) {};
};

