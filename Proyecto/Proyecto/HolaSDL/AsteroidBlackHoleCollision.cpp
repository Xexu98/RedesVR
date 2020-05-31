#include "AsteroidBlackHoleCollision.h"
#include "GameManager.h"
#include "Messages_defs.h"


AsteroidBlackHoleCollision::AsteroidBlackHoleCollision(GameManager* g):gameMgr_(g)
{
}


AsteroidBlackHoleCollision::~AsteroidBlackHoleCollision()
{
}

void AsteroidBlackHoleCollision::update(Container* c, Uint32 time)
{
	if (gameMgr_->getRun())
	{
		if (asteroids_ != nullptr && blackholes_ != nullptr) {
			for (auto it = asteroids_->begin(); it < asteroids_->end(); it++)
			{
				if ((*it)->isActive())
				{
					for (auto bit = blackholes_->begin(); bit < blackholes_->end(); bit++)
					{
						if ((*bit)->isActive())
						{
							//3- check Fighter Vs Asterorids collision
							if (Collisions::collidesWithRotation((*it), (*bit))) {
								//send message
								c->globalSend(this, msg::BlackHoleAsteroidCollision(c->getId(), msg::Broadcast, (*bit), (*it)));
							}
						}
					}
				}
			}
		}
	}
}

void AsteroidBlackHoleCollision::receive(Container* c, const msg::Message& msg)
{
	switch (msg.type_)
	{
	case msg::ASTEROIDS_INFO:
	{
		const vector<Asteroid*>* a = static_cast<const msg::AsteroidsInfo&>(msg).asteroids_;
		asteroids_ = a;
	}
	break;
	case msg::BLACKHOLE_INFO:
	{
		const vector<BlackHole*>* bh = static_cast<const msg::BlackHoleInfo&>(msg).blackHoles_;
		blackholes_ = bh;
	}
	break;
	}
}