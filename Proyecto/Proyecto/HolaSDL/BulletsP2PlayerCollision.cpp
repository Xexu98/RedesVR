#include "BulletsP2PlayerCollision.h"
#include "GameManager.h"
#include "Messages_defs.h"


BulletsP2PlayerCollision::BulletsP2PlayerCollision(GameManager * g) :gameMgr_(g)
{

}

BulletsP2PlayerCollision::~BulletsP2PlayerCollision()
{

}

void BulletsP2PlayerCollision::update(Container * c, Uint32 time)
{
	if (bulletsp2_ != nullptr && player_ != nullptr) {
		//1-check game is run
		if (gameMgr_->getRun())
		{	//2- check Asteroid and Fighter is Active
			if (player_->isActive()) {
				for (auto it = (*bulletsp2_).begin(); it < (*bulletsp2_).end(); it++) {
					if ((*it) != nullptr && (*it)->isActive()) {
						//3- check Fighter Vs Asterorids collision
						if (Collisions::collidesWithRotation(player_, (*it))) {
							//send message
							c->globalSend(this, msg::BulletP2PlayerCollision(c->getId(), msg::Broadcast,(*it),player_));
						}
					}
				}
			}
		}
	}
}

void BulletsP2PlayerCollision::receive(Container * c, const msg::Message & msg)
{
	Component::receive(c, msg);

	switch (msg.type_)
	{
	case msg::BULLETSP2_INFO:
	{
		const vector<BulletP2*>* b = static_cast<const msg::BulletsP2InfoMsg&>(msg).bullets_;
		bulletsp2_ = b;
	}
	break;
	case msg::PLAYER_INFO:
		GameObject* p = static_cast<const msg::PlayerInfo&>(msg).player_;
		player_ = p;
		break;
	}
}
