#include "FighterBlackHoleCollision.h"
#include "Messages_defs.h"
#include "GameManager.h"


FighterBlackHoleCollision::FighterBlackHoleCollision(GameManager* g):gameMgr_(g)
{
}


FighterBlackHoleCollision::~FighterBlackHoleCollision()
{
}

void FighterBlackHoleCollision::update(Container* c, Uint32 time)
{
	if (blackhs_ != nullptr && fighter_ != nullptr)
	{
		if (gameMgr_->getRun())
		{	//2- check Asteroid and Fighter is Active
			if (fighter_->isActive()) {
				for (auto it = blackhs_->begin(); it < blackhs_->end(); it++) {
					if ((*it) != nullptr && (*it)->isActive()) {
						//3- check Fighter Vs Asterorids collision
						if (Collisions::collidesWithRotation(fighter_, (*it))) {
							//send message
							c->globalSend(this, msg::FighterBlackHoleCollisionMsg(c->getId(), msg::Broadcast, fighter_, (*it)));
						}
					}
				}
			}
		}
	}
}

void FighterBlackHoleCollision::receive(Container* c, const msg::Message& msg)
{
	Component::receive(c, msg);
	switch (msg.type_)
	{
	case msg::BLACKHOLE_INFO:
	{
		const vector<BlackHole*>* bhs = static_cast<const msg::BlackHoleInfo&>(msg).blackHoles_;
		blackhs_ = bhs;
	}
	break;
	case msg::PLAYER_INFO:
		GameObject* f = static_cast<const msg::PlayerInfo&>(msg).player_;
		fighter_ = f;
		break;
	}
}
