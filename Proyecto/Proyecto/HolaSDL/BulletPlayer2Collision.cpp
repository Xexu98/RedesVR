#include "BulletPlayer2Collision.h"
#include "GameManager.h"
#include "Messages_defs.h"

BulletPlayer2Collision::BulletPlayer2Collision(GameManager * g):gameMgr_(g)
{

}

BulletPlayer2Collision::~BulletPlayer2Collision()
{

}

void BulletPlayer2Collision::update(Container * c, Uint32 time)
{
	if (bullets_ != nullptr && player2_ != nullptr) {
		//1-check game is run
		if (gameMgr_->getRun())
		{	//2- check Asteroid and Fighter is Active
			if (player2_->isActive()) {
				for (auto it = (*bullets_).begin(); it < (*bullets_).end(); it++) {
					if ((*it) != nullptr && (*it)->isActive()) {
						//3- check Fighter Vs Asterorids collision
						if (Collisions::collidesWithRotation(player2_, (*it))) {
							//send message
							c->globalSend(this, msg::BulletPlayer2Collision(c->getId(), msg::Broadcast, (*it),player2_));
						}
					}
				}
			}
		}
	}
}

void BulletPlayer2Collision::receive(Container * c, const msg::Message & msg)
{
	Component::receive(c, msg);

	switch (msg.type_)
	{
	case msg::BULLETS_INFO:
	{
		const vector<Bullet*>* b = static_cast<const msg::BulletsInfoMsg&>(msg).bullets_;
		bullets_ = b;
	}
	break;
	case msg::PLAYER2_INFO:
		GameObject* p = static_cast<const msg::PlayerInfo2&>(msg).player2_;
		player2_ = p;
		break;
	}
}
