#include "BulletBlackHoleCollision.h"
#include "GameManager.h"
#include "Messages_defs.h"


BulletBlackHoleCollision::BulletBlackHoleCollision(GameManager* g):gameMgr_(g)
{
}


BulletBlackHoleCollision::~BulletBlackHoleCollision()
{
}

void BulletBlackHoleCollision::update(Container* c, Uint32 time)
{
	if (gameMgr_->getRun())
	{
		//check Bullets and Asteroids have value
		if (blackholes_ != nullptr && bullets_ != nullptr) {
			for (auto it = blackholes_->begin(); it < blackholes_->end(); it++)
			{
				if ((*it)->isActive())
				{
					for (auto bit = bullets_->begin(); bit < bullets_->end(); bit++)
					{
						if ((*bit)->isActive())
						{
							//3- check Fighter Vs Asterorids collision
							if (Collisions::collidesWithRotation((*it), (*bit))) {
								//send message
								c->globalSend(this, msg::BulletBlackHoleCollision(c->getId(), msg::Broadcast, (*bit), (*it)));
							}
						}
					}
				}
			}
		}
	}
}

void BulletBlackHoleCollision::receive(Container* c, const msg::Message& msg)
{
	Component::receive(c, msg);

	switch (msg.type_)
	{
	case msg::BLACKHOLE_INFO:
	{
		const vector<BlackHole*>* bh = static_cast<const msg::BlackHoleInfo&>(msg).blackHoles_;
		blackholes_ = bh;
	}
	break;
	case msg::BULLETS_INFO:
	{
		const vector <Bullet*>* b = static_cast<const msg::BulletsInfoMsg&>(msg).bullets_;
		bullets_ = b;
	}
	break;
	}
}