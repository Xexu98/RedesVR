#pragma once

#include "InputComponent.h"

class ThrustICP2 : public InputComponent
{
public:
	ThrustICP2();
	virtual ~ThrustICP2();
	virtual void handleInput(Container* c, Uint32 time);
	virtual void receive(Container* c, const msg::Message& msg);

private:
	double thrust = 2.0;
	double speedLimit = 15.0;
	Vector2D v;
};

