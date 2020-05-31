#include "ThrustIC.h"

#include "Player.h"

#include "InputHandler.h"

ThrustIC::ThrustIC()
{
}


ThrustIC::~ThrustIC()
{
}

void ThrustIC::handleInput(Container* c, Uint32 time) {
	if (InputHandler::getInstance()->isAnyKeyDown()) {
		if (InputHandler::getInstance()->isKeyDown(SDLK_w)) {
			v = static_cast<Player*>(c)->getVelocity() + Vector2D(0, -1)*thrust;
			if (v.magnitude()>speedLimit)
			{
				v = v.normalize()*speedLimit;
			}
			c->setVelocity(v);
		}
		else if (InputHandler::getInstance()->isKeyDown(SDLK_s))
		{
			v = static_cast<Player*>(c)->getVelocity() + Vector2D(0, 1)*thrust;
			if (v.magnitude() > speedLimit)
			{
				v = v.normalize()*speedLimit;
			}
			c->setVelocity(v);
		}
		else if (InputHandler::getInstance()->isKeyDown(SDLK_d))
		{
			v = static_cast<Player*>(c)->getVelocity() + Vector2D(1, 0)*thrust;
			if (v.magnitude() > speedLimit)
			{
				v = v.normalize()*speedLimit;
			}
			c->setVelocity(v);
		}
		else if (InputHandler::getInstance()->isKeyDown(SDLK_a))
		{
			v = static_cast<Player*>(c)->getVelocity() + Vector2D(-1, 0)*thrust;
			if (v.magnitude() > speedLimit)
			{
				v = v.normalize()*speedLimit;
			}
			c->setVelocity(v);
		}
	}
	else
	{
		c->setVelocity(Vector2D(0,0));
	}
}

void ThrustIC::receive(Container * c, const msg::Message & msg)
{
}
