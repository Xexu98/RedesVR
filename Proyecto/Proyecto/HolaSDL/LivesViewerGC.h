#pragma once
#include "GraphicsComponent.h"

class GameManager;
class LivesViewerGC:public GraphicsComponent
{
public:
	LivesViewerGC(GameManager* g);
	~LivesViewerGC();
	virtual void render(Container* c, Uint32 time);
private:
	GameManager* gameMgr_;
};

