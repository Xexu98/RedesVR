#pragma once
#include "InputComponent.h"

class GameManager;

class GameCrtlIC: public InputComponent
{
public:

	GameCrtlIC(GameManager* g);
	virtual ~GameCrtlIC();
	virtual void handleInput(Container* c, Uint32 time);

private:
	GameManager* gameMgr_;
};

