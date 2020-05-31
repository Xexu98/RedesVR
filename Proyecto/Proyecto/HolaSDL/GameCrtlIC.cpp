#include "GameCrtlIC.h"
#include "Messages_defs.h"
#include "GameManager.h"
#include "InputHandler.h"


GameCrtlIC::GameCrtlIC(GameManager* g): gameMgr_(g)
{
}


GameCrtlIC::~GameCrtlIC()
{
}

void GameCrtlIC::handleInput(Container* c, Uint32 time)
{
	//if running = false
	if (!gameMgr_->getRun()) {
		if (InputHandler::getInstance()->isAnyKeyDown()) {
			if (InputHandler::getInstance()->isKeyDown(SDLK_RETURN)) {
				//if new Game
				if (gameMgr_->getOver()) {
					if ((gameMgr_->getScore() == 0 && gameMgr_->getLives() == 3) || gameMgr_->getLives() == 0 || gameMgr_->getVictoryCount() == 3)
						c->globalSend(this, msg::Message(msg::GAME_START, c->getId(), msg::Broadcast));
				}
				c->globalSend(this, msg::Message(msg::ROUND_START, c->getId(), msg::Broadcast));
			}
		}
	}
}
