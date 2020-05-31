#include "GameStatusViewGC.h"
#include "GameManager.h"
#include "Logger.h"



GameStatusViewGC::GameStatusViewGC(GameManager* g):gameMgr_(g)
{	
}

GameStatusViewGC::~GameStatusViewGC()
{
}

void GameStatusViewGC::render(Container* c, Uint32 time)
{
	Texture* msg0;
	if (gameMgr_->getWinner() == 0)
	{
		 msg0 = new Texture(c->getGame()->getRenderer(),
			"Game Over",
			*(c->getGame()->getServiceLocator()->getFonts()->getFont(
				Resources::ARIAL24)), { COLOR(0x0022ffff) });
	}
	else if (gameMgr_->getWinner() == 2)
	{
		 msg0 =new Texture(c->getGame()->getRenderer(),
			"Game Over: Asteroids Wins",
			*(c->getGame()->getServiceLocator()->getFonts()->getFont(
				Resources::ARIAL24)), { COLOR(0x0022ffff) });
	}
	else
	{
		 msg0 = new Texture(c->getGame()->getRenderer(),
			"Game Over: Figther Win",
			*(c->getGame()->getServiceLocator()->getFonts()->getFont(
				Resources::ARIAL24)), { COLOR(0x0022ffff) });
	}

	Texture msg1(c->getGame()->getRenderer(),
		"Press ENTER to continue",
		*(c->getGame()->getServiceLocator()->getFonts()->getFont(
			Resources::ARIAL24)), { COLOR(0x0022ffff) });

	Texture msg2(c->getGame()->getRenderer(),
		"Press ENTER to start a new game",
		*(c->getGame()->getServiceLocator()->getFonts()->getFont(
			Resources::ARIAL24)), { COLOR(0x0022ffff) });

	Texture msg3(c->getGame()->getRenderer(),
		"Press ENTER to start a New Round",
		*(c->getGame()->getServiceLocator()->getFonts()->getFont(
			Resources::ARIAL24)), { COLOR(0x0022ffff) });


	//if Running = false
	if (!gameMgr_->getRun()) {
		//if GameOver
		if (gameMgr_->getOver()) {
			msg0->render(c->getGame()->getRenderer(), c->getGame()->getWindowWidth() / 2 - msg0->getWidth() / 2, c->getGame()->getWindowHeight() - 150);
		}

		//if round over
		if ((gameMgr_->getScore() != 0 || gameMgr_->getLives() != 0) && !gameMgr_->getOver())
		{
			msg1.render(c->getGame()->getRenderer(), c->getGame()->getWindowWidth() / 2 - msg0->getWidth() / 2 - 100, c->getGame()->getWindowHeight() - 100);
			Logger::getInstance()->log("Game Over"); //write info in ofstream log_
		}

		else if ((gameMgr_->getNextRound()) && !(gameMgr_->getGameWin())) {
			msg3.render(c->getGame()->getRenderer(), c->getGame()->getWindowWidth() / 2 - msg0->getWidth() / 2 - 100, c->getGame()->getWindowHeight() - 100);
		}

		else if ((gameMgr_->getGameWin()) && (gameMgr_->getNextRound())) {
			msg2.render(c->getGame()->getRenderer(), c->getGame()->getWindowWidth() / 2 - msg0->getWidth() / 2 - 100, c->getGame()->getWindowHeight() - 100);
			Logger::getInstance()->log("Game Win"); //write info in ofstream log_
		}
		else
		{
			msg2.render(c->getGame()->getRenderer(), c->getGame()->getWindowWidth() / 2 - msg0->getWidth() / 2 - 100, c->getGame()->getWindowHeight() - 100);
		}
	}
	
}
