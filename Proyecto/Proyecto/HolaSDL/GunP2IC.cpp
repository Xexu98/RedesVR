#include "GunP2IC.h"
#include "Messages_defs.h"
#include "InputHandler.h"
#include "Logger.h"

#include <sstream>

GunP2IC::GunP2IC()
{
}

GunP2IC::~GunP2IC()
{
}

void GunP2IC::handleInput(Container * c, Uint32 time)
{
	if (InputHandler::getInstance()->getMouseButtonState(2)) {
		Vector2D p = c->getPosition() + Vector2D(c->getWidth() / 2.0, c->getHeight() / 2.0) + Vector2D(0.0, -(c->getHeight() / 2.0 + 5.0)).rotate(c->getRotation());
		Vector2D d = Vector2D(0, -1).rotate(c->getRotation());
		c->globalSend(this, msg::ShootP2(c->getId(), msg::Broadcast, p, d, 0));


		Logger::getInstance()->log([p, d]() {

			stringstream s;
			s << "ShootingP2: " << p << " " << d;
			return s.str();
		});
	}
}
