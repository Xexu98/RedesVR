#pragma once
#include "PhysicsComponent.h"

class RotatingPC : public PhysicsComponent
{
public:
	RotatingPC(double alpha);
	virtual ~RotatingPC();
	virtual void update(Container* c, Uint32 time); 

private:
	double alpha_;
};

