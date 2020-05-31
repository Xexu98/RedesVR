#pragma once
#include "PhysicsComponent.h"

class ReduceSpeedPC : public PhysicsComponent
{
public:
	ReduceSpeedPC(double factor);
	virtual ~ReduceSpeedPC();
	virtual void update(Container* c, Uint32 time);
private:
	double factor_;
	Vector2D v;
};

