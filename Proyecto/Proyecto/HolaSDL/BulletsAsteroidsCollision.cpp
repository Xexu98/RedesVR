#include "BulletsAsteroidsCollision.h"
#include "GameManager.h"
#include "Messages_defs.h"


BulletsAsteroidsCollision::BulletsAsteroidsCollision(GameManager* g):gameMgr_(g)
{
}


BulletsAsteroidsCollision::~BulletsAsteroidsCollision()
{
}

void BulletsAsteroidsCollision::update(Container* c, Uint32 time)
{
	//it = asteroids; bit = bullet
	if (gameMgr_->getRun())
	{
		//check Bullets and Asteroids have value
		if (asteroids_ != nullptr && bullets_ != nullptr) {
			for (auto it = asteroids_->begin(); it < asteroids_->end(); it++)
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
								c->globalSend(this, msg::BulletAsteroidCollision(c->getId(), msg::Broadcast, (*bit), (*it)));
							}
						}
					}
				}
			}
		}
	}
}

void BulletsAsteroidsCollision::receive(Container * c, const msg::Message & msg)
{
	Component::receive(c, msg);

	switch (msg.type_)
	{
	case msg::ASTEROIDS_INFO:
	{
		const vector<Asteroid*>* a = static_cast<const msg::AsteroidsInfo&>(msg).asteroids_;
		asteroids_ = a;
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
