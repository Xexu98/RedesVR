#include "Player.h"
#include "Messages_defs.h"



Player::Player(SDLGame* game) :
	Container(game),
	fighterImage_(game->getServiceLocator()->getTextures()->getTexture(Resources::Player)),
	naturalMove_(),
	oppositeSide_(),
	rotation_(),
	thrust_(),
	normalGun_(),
	reduceSpeed_(0.995)
{
	setWidth(60);
	setHeight(80);
	addC(&fighterImage_);
	addC(&naturalMove_);
	addC(&oppositeSide_);
	addC(&rotation_);
	addC(&reduceSpeed_);
	addC(&normalGun_);
	addC(&thrust_);
	setActive(false);
	reset();
	setId(msg::Player);
}


Player::~Player()
{
}

void Player::receive(const void * senderObj, const msg::Message & msg)
{
	Container::receive(senderObj, msg);
	switch (msg.type_) {
	case  msg::GAME_START:
		life = 100;
		globalSend(this, msg::PlayerInfo(this->getId(),msg::Broadcast,this));
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
	case msg::BULLETP2_PLAYER_COLLISION:
		life =life- 20;
		if (life <= 0)
		{
			globalSend(this, msg::Message(msg::NO_LIFE_PLAYER, getId(), msg::Broadcast));
		}
		break;
	}
}

void Player::reset() {
	setPosition(Vector2D(getGame()->getWindowWidth() / 2, getGame()->getWindowHeight() / 2));
}
