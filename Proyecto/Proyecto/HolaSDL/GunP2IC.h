#pragma once
#include "InputComponent.h"


class GunP2IC : public InputComponent
{
public:
	GunP2IC();
	virtual ~GunP2IC();
	virtual void handleInput(Container* c, Uint32 time);
};
