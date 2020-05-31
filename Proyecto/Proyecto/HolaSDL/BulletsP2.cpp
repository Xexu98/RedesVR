#include "BulletsP2.h"
#include "Messages_defs.h"

BulletsP2::BulletsP2(SDLGame * game):GameObjectPool(game),
naturalMove_(),
deactivate_(),
bulletImage_(game->getServiceLocator()->getTextures()->getTexture(Resources::RedRect))
{
	for (BulletP2*b : getAllObjects())
	{
		b->addC(&bulletImage_);
		b->addC(&naturalMove_);
		b->addC(&deactivate_);
		b->setActive(false);
		b->setId(msg::BulletsShooter);
	}
}

BulletsP2::~BulletsP2()
{
}

void BulletsP2::receive(const void * senderObj, const msg::Message & msg)
{
	Container::receive(senderObj, msg);
	switch (msg.type_) {
	case msg::GAME_START:
		this->globalSend(this, msg::BulletsP2InfoMsg(getId(), msg::Broadcast, &getAllObjects()));
		break;
	case msg::ROUND_START:
		setActive(true);
		break;
	case msg::ROUND_OVER:
		this->deactiveAllObjects();
		setActive(false);
		break;
	case msg::BULLET_ASTEROID_COLLISION:
		//Asteroid* asteroidBroken = static_cast<const msg::BulletAsteroidCollision&>(msg).asteroid_;
	{
		//BulletP2* bullethit = static_cast<const msg::BulletAsteroidCollision&>(msg).bullet_;
		//bullethit->setActive(false);
	}
	break;
	case msg::BULLET_BLACKHOLE_COLLISION:
	{
		//BulletP2* bullethit = static_cast<const msg::BulletBlackHoleCollision&>(msg).bullet_;
		//bullethit->setActive(false);
	}
	break;
	case msg::BULLETP2_PLAYER_COLLISION:
	{
		BulletP2* bullethit = static_cast<const msg::BulletP2PlayerCollision&>(msg).bullet_;
		bullethit->setActive(false);
	}
		break;
	case msg::PLAYER2_SHOOT:
		if (allBulletsOut() != 10)
		{
			getGame()->getServiceLocator()->getAudios()->playChannel(Resources::GunShot, 0, 2); //diferent channel for play various sounds together
			Vector2D P = static_cast<const msg::Shoot&>(msg).pos_;
			Vector2D D = static_cast<const msg::Shoot&>(msg).dir_;
			BulletP2 *b = getUnusedObject();
			b->setWidth(1);
			b->setHeight(5);
			b->setPosition(P - Vector2D(width_ / 2, height_));
			b->setVelocity(D * 5);
			b->setRotation(Vector2D(0, -1).angle(D));
			b->setActive(true);

		}

		break;
	}
}

int BulletsP2::allBulletsOut()
{
	int contbull = 0;
	for (BulletP2*b : getAllObjects())
	{
		if (b->isActive())
		{
			contbull++;
		}
	}
	return contbull;
}
