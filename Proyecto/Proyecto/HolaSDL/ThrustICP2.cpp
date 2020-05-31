#include "ThrustICP2.h"

#include "Player2.h"

#include "InputHandler.h"

ThrustICP2::ThrustICP2()
{
}


ThrustICP2::~ThrustICP2()
{
}

void ThrustICP2::handleInput(Container* c, Uint32 time) {
	if (InputHandler::getInstance()->isAnyKeyDown()) {
		if (InputHandler::getInstance()->isKeyDown(SDLK_UP)) {
			v = static_cast<Player2*>(c)->getVelocity() + Vector2D(0, -1)*thrust;
			if (v.magnitude() > speedLimit)
			{
				v = v.normalize()*speedLimit;
			}
			c->setVelocity(v);
		}
		else if (InputHandler::getInstance()->isKeyDown(SDLK_DOWN))
		{
			v = static_cast<Player2*>(c)->getVelocity() + Vector2D(0, 1)*thrust;
			if (v.magnitude() > speedLimit)
			{
				v = v.normalize()*speedLimit;
			}
			c->setVelocity(v);
		}
		else if (InputHandler::getInstance()->isKeyDown(SDLK_RIGHT))
		{
			v = static_cast<Player2*>(c)->getVelocity() + Vector2D(1, 0)*thrust;
			if (v.magnitude() > speedLimit)
			{
				v = v.normalize()*speedLimit;
			}
			c->setVelocity(v);
		}
		else if (InputHandler::getInstance()->isKeyDown(SDLK_LEFT))
		{
			v = static_cast<Player2*>(c)->getVelocity() + Vector2D(-1, 0)*thrust;
			if (v.magnitude() > speedLimit)
			{
				v = v.normalize()*speedLimit;
			}
			c->setVelocity(v);
		}
	}
	else
	{
		c->setVelocity(Vector2D(0, 0));
	}
}

void ThrustICP2::receive(Container * c, const msg::Message & msg)
{
}
