#include "FighterAsteroidCollision.h"
#include "Messages_defs.h"
#include "GameManager.h"
#include "Collisions.h"


FighterAsteroidCollision::FighterAsteroidCollision(GameManager* g):gameMgr_(g)
{
}


FighterAsteroidCollision::~FighterAsteroidCollision()
{
}
void FighterAsteroidCollision::update(Container* c, Uint32 time)
{
	//Asteroid and Fighter have value
	if (asteroids_ != nullptr && fighter_ != nullptr) {
		//1-check game is run
		if (gameMgr_->getRun())
		{	//2- check Asteroid and Fighter is Active
			if (fighter_->isActive()) {
				for (auto it = (*asteroids_).begin(); it < (*asteroids_).end(); it++) {
					if ((*it) != nullptr && (*it)->isActive()) {
						//3- check Fighter Vs Asterorids collision
						if (Collisions::collidesWithRotation(fighter_, (*it))) {
							//send message
							c->globalSend(this, msg::FighterAsteroidCollisionMsg(c->getId(), msg::Broadcast, fighter_, (*it)));
						}
					}
				}
			}
		}
	}
}

void FighterAsteroidCollision::receive(Container * c, const msg::Message & msg)
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
	case msg::PLAYER_INFO:
		GameObject* f = static_cast<const msg::PlayerInfo&>(msg).player_;
		fighter_ = f;
		break;
	}
}

