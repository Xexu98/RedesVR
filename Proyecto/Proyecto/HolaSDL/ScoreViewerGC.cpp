#include "ScoreViewerGC.h"
#include "GameManager.h"


ScoreViewerGC::ScoreViewerGC(GameManager* g):gameMgr_(g)
{
}


ScoreViewerGC::~ScoreViewerGC()
{
}

void ScoreViewerGC::render(Container* c, Uint32 time)
{
	Texture msg0(c->getGame()->getRenderer(),
		"Score: ",
		*(c->getGame()->getServiceLocator()->getFonts()->getFont(
			Resources::ARIAL24)), { COLOR(0x0022ffff) });
	msg0.render(c->getGame()->getRenderer(), 150, 0);
	Texture msg1(c->getGame()->getRenderer(),
		to_string(gameMgr_->getScore()),
		*(c->getGame()->getServiceLocator()->getFonts()->getFont(
			Resources::ARIAL24)), { COLOR(0x0022ffff) });
	msg1.render(c->getGame()->getRenderer(), 225, 0);
}
