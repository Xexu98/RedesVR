#include "Player2.h"
#include "Messages_defs.h"


Player2::Player2(SDLGame* game) :
	Container(game),
	player2Image_(game->getServiceLocator()->getTextures()->getTexture(Resources::Player2)),
	naturalMove_(),
	oppositeSide_(),
	rotation_(),
	thrust_(),
	normalGun_(),
	reduceSpeed_(0.995)
{
	setWidth(60);
	setHeight(80);
	addC(&player2Image_);
	addC(&naturalMove_);
	addC(&oppositeSide_);
	addC(&rotation_);
	addC(&reduceSpeed_);
	addC(&normalGun_);
	addC(&thrust_);
	setActive(false);
	reset();
	setId(msg::Player2);
}

Player2::~Player2()
{
}


void Player2::receive(const void * senderObj, const msg::Message & msg)
{
	Container::receive(senderObj, msg);
	switch (msg.type_) {
	case  msg::GAME_START:
		life = 100;
		globalSend(this, msg::PlayerInfo2(this->getId(), msg::Broadcast, this));
		break;
	case msg::ROUND_START:
		reset();
		setVelocity(Vector2D(0.0, 0.0));
		setActive(true);
		life = 100;
		break;
	case msg::ROUND_OVER:
		setActive(false);
		break;
	case msg::BULLET_PLAYER2_COLLISION:
		life =life-20;
		if (life <= 0)
		{
			globalSend(this, msg::Message(msg::NO_LIFE_PLAYER2, getId(), msg::Broadcast));
		}
		break;
	}
}
void Player2::reset() {
	setPosition(Vector2D(getGame()->getWindowWidth() / 3, getGame()->getWindowHeight() / 2));
}