#include "Asteroid.h"



Asteroid::Asteroid():Container()
{

}


Asteroid::~Asteroid()
{

}
void Asteroid::reset() {
	setPosition(Vector2D(getGame()->getWindowWidth() /((rand()%5)+1) - 6, getGame()->getWindowHeight() /((rand()%5)+1) - 6));
}