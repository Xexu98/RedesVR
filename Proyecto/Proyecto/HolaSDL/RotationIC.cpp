#include "RotationIC.h"

#include "Player.h"

#include "InputHandler.h"

RotationIC::RotationIC()
{
}


RotationIC::~RotationIC()
{
}

void RotationIC::handleInput(Container* c, Uint32 time) {
			int x, y;
			SDL_GetMouseState(&x, &y);
			float angle = -90 + (atan2((c->getPosition().getY() - y), (c->getPosition().getX() - x))*180.0000) / 3.1416;
			if (angle>=0)
			{
				static_cast<Player*>(c)->setRotation(360+angle);
			}
			else
			{
				static_cast<Player*>(c)->setRotation(angle);
			}
			
	
}

void RotationIC::receive(Container * c, const msg::Message & msg)
{
}
