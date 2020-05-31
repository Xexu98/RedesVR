#pragma once
#include "InputComponent.h"

class RotationIC : public InputComponent
{
public:
	RotationIC();
	virtual ~RotationIC();
	virtual void handleInput(Container* c, Uint32 time);
	virtual void receive(Container* c, const msg::Message& msg);
};

