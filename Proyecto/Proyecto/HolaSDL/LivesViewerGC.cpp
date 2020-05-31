#include "LivesViewerGC.h"
#include "GameManager.h"


LivesViewerGC::LivesViewerGC(GameManager* g):gameMgr_(g)
{
}


LivesViewerGC::~LivesViewerGC()
{
}

void LivesViewerGC::render(Container* c, Uint32 time)
{
	Texture msg0(c->getGame()->getRenderer(),
		"Lives:",
		*(c->getGame()->getServiceLocator()->getFonts()->getFont(
			Resources::ARIAL24)), { COLOR(0x0022ffff) });
	msg0.render(c->getGame()->getRenderer(),0,0);
	Texture msg1(c->getGame()->getRenderer(),
		to_string(gameMgr_->getLives()),
		*(c->getGame()->getServiceLocator()->getFonts()->getFont(
			Resources::ARIAL24)), { COLOR(0x0022ffff) });
	msg1.render(c->getGame()->getRenderer(), 65, 0);
}
