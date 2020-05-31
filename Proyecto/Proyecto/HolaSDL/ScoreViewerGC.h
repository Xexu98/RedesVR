#pragma once
#include "GraphicsComponent.h"

class GameManager;
class ScoreViewerGC:public GraphicsComponent
{
public:
	ScoreViewerGC(GameManager* g);
	virtual ~ScoreViewerGC();
	virtual void render(Container* c, Uint32 time);
private:
	GameManager* gameMgr_;
};

