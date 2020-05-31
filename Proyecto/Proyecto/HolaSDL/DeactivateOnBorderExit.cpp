#include "DeactivateOnBorderExit.h"



DeactivateOnBorderExit::DeactivateOnBorderExit()
{
}


DeactivateOnBorderExit::~DeactivateOnBorderExit()
{
}

void DeactivateOnBorderExit::update(Container* c, Uint32 time)
{
	double heigt = c->getGame()->getWindowHeight(), widht = c->getGame()->getWindowWidth(), x = c->getPosition().getX(), y = c->getPosition().getY();

	if (x < 0 || y < 0 || x > widht || y > heigt)
	{
		c->setActive(false);
	}
}