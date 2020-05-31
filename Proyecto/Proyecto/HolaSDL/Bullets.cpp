#include "Bullets.h"
#include "Messages_defs.h"


Bullets::Bullets(SDLGame* game):GameObjectPool(game),
	naturalMove_(),
	deactivate_(),
	bulletImage_(game->getServiceLocator()->getTextures()->getTexture(Resources::WhiteRect))
{
	for (Bullet*b : getAllObjects())
	{
		b->addC(&bulletImage_);
		b->addC(&naturalMove_);
		b->addC(&deactivate_);
		b->setActive(false);
		b->setId(msg::BulletsShooter);
	}
	
}

Bullets::~Bullets()
{
}

void Bullets::receive(const void* senderObj, const msg::Message& msg)
{
	Container::receive(senderObj, msg);
	switch (msg.type_) {
	case msg::GAME_START:
		this->globalSend(this, msg::BulletsInfoMsg(getId(), msg::Broadcast, &getAllObjects()));
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
		Bullet* bullethit = static_cast<const msg::BulletAsteroidCollision&>(msg).bullet_;
		bullethit->setActive(false);
	}
	break;
	case msg::BULLET_BLACKHOLE_COLLISION:
	{
		Bullet* bullethit = static_cast<const msg::BulletBlackHoleCollision&>(msg).bullet_;
		bullethit->setActive(false);
	}
		break;
	case msg::BULLET_PLAYER2_COLLISION:
	{
		Bullet* bullethit = static_cast<const msg::BulletPlayer2Collision&>(msg).bullet_;
		bullethit->setActive(false);
	}
		break;
	case msg::PLAYER_SHOOT:
		if (allBulletsOut() != 10)
		{	
			getGame()->getServiceLocator()->getAudios()->playChannel(Resources::GunShot, 0, 2); //diferent channel for play various sounds together
			Vector2D P = static_cast<const msg::Shoot&>(msg).pos_;
			Vector2D D = static_cast<const msg::Shoot&>(msg).dir_;
			Bullet *b = getUnusedObject();
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
int Bullets::allBulletsOut()
{
	int contbull=0;
	for (Bullet*b : getAllObjects())
	{
		if (b->isActive())
		{
			contbull++;
		}
	}
	return contbull;
}
/*void Bullets::creaPrueba()
{
	Bullet *b = getUnusedObject();
	b->setActive(true);
	b->setWidth(5);
	b->setHeight(20);
	b->setPosition(Vector2D(getGame()->getWindowWidth() / 2 - 6, getGame()->getWindowHeight() / 2 - 6));
	b->setVelocity(Vector2D(0.0, -1.0));

}*/
