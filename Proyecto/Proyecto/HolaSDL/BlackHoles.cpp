#include "BlackHoles.h"
#include "Logger.h"
#include "Collisions.h"
#include "Messages_defs.h"
#include <sstream>

#include "AsteroidsGame.h"



BlackHoles::BlackHoles(SDLGame* game):GameObjectPool(game),
naturalMove_(), rotating_(-3.0),
blackHoleImg_(game->getServiceLocator()->getTextures()->getTexture(Resources::BlackHole))
{
	for (BlackHole* bh : getAllObjects())
	{
		bh->setWidth(50);
		bh->setHeight(50);
		bh->addC(&blackHoleImg_);
		bh->addC(&naturalMove_);
		bh->addC(&rotating_);
		bh->setActive(false);
		bh->setId(msg::BlackHoles);
	}
	
}


BlackHoles::~BlackHoles()
{
}

void BlackHoles::receive(const void* senderObj, const msg::Message& msg)
{
	Container::receive(senderObj, msg);
	switch (msg.type_) {
	case msg::GAME_START:
		numgen = 1;
		this->globalSend(this, msg::BlackHoleInfo(getId(), msg::Broadcast, &getAllObjects()));
		break;
	case msg::ROUND_START:
		setActive(true);
		colocaBlackHole();
		break;
	case msg::ROUND_OVER:
		this->deactiveAllObjects();
		setActive(false);
		break;
	case msg::NO_MORE_ASTEROIDS:
		numgen++;
		break;
	}
}



void BlackHoles::colocaBlackHole()
{
	int numbh = numgen * 2;
	BlackHole* bh [8];
	int height;
	int width;
	RandomNumberGenerator* r = getGame()->getServiceLocator()->getRandomGenerator();

	AsteroidsGame* g = static_cast<AsteroidsGame*>(getGame());

	for (int i = 0; i < numbh; i++)
	{
		bh[i] = getUnusedObject();
			
		width = r->nextInt(0 + bh[i]->getWidth(), 800 - bh[i]->getWidth());
		height = r->nextInt(0 + bh[i]->getHeight(), 600 - bh[i]->getHeight());
		bh[i]->setPosition(Vector2D(width, height));

		while(Collisions::collidesWithRotation(bh[i], g->getFighter()))
		{
			width = r->nextInt(0 + bh[i]->getWidth(), 800 - bh[i]->getWidth());
			height = r->nextInt(0 + bh[i]->getHeight(), 600 - bh[i]->getHeight());
			bh[i]->setPosition(Vector2D(width, height));
		}

		bh[i]->setActive(true);
		Vector2D p = bh[i]->getPosition();
		Vector2D v(0.0, 0.0);
		Logger::getInstance()->log([p, v]() {
			stringstream s;
			s << "New blackhole: " << p << " " << v;
			return s.str();
		});
	}

}
