#include "ShowUpAtOppositeSidePC.h"



ShowUpAtOppositeSidePC::ShowUpAtOppositeSidePC()
{
}


ShowUpAtOppositeSidePC::~ShowUpAtOppositeSidePC()
{
}


void ShowUpAtOppositeSidePC::update(Container* c, Uint32 time) {

		double heigt = c->getGame()->getWindowHeight(),  widht = c->getGame()->getWindowWidth(), x = c->getPosition().getX(), y = c->getPosition().getY();

		Vector2D newPos = { NULL, NULL };
		if (x < 0) { newPos.setX(widht); }
		else if (x > widht) { newPos.setX(0.0); }
		else { newPos.setX(x); }
		if (y < 0) { newPos.setY(heigt); }
		else if (y > heigt) { newPos.setY(0.0); }
		else { newPos.setY(y); }

		if (newPos.getX() != NULL || newPos.getY() != NULL){ c->setPosition(newPos); }
	
}

void ShowUpAtOppositeSidePC::receive(Container * c, const msg::Message & msg)
{
}
