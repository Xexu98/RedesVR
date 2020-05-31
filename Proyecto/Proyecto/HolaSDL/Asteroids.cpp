#include "Asteroids.h"
#include "Messages_defs.h"
#include "Logger.h"
#include <sstream>
#include "Collisions.h"
#include "AsteroidsGame.h"


Asteroids::Asteroids(SDLGame* game):GameObjectPool(game),
asteroidImage_(game->getServiceLocator()->getTextures()->getTexture(Resources::Asteroid)),
	naturalMove_(),
	rotating_(4.0),
	showUpAtOppositeSide_()
{
	generations_ = 2;
	for (Asteroid*a:getAllObjects())
	{
		//a = getUnusedObject();
		
		a->setWidth(20);
		a->setHeight(20);
		a->setActive(true);
		a->addC(&asteroidImage_);
		a->addC(&naturalMove_);
		a->addC(&rotating_);
		a->addC(&showUpAtOppositeSide_);
		a->setActive(false);
		a->setId(msg::Asteroids);
	}
}


Asteroids::~Asteroids()
{
}
void Asteroids::receive(const void* senderObj, const msg::Message& msg)
{
	Container::receive(senderObj, msg);
	switch (msg.type_) {
	case msg::GAME_START: {
		this->globalSend(this, msg::AsteroidsInfo(getId(), msg::Broadcast, &getAllObjects()));
		break;
	}
	case msg::ROUND_START: {
		setActive(true);
		colocaAsteroides(10);
		break;
	}
	case msg::ROUND_OVER: {
		this->deactiveAllObjects();
		setActive(false);
		break;
	}

	case msg::BULLET_ASTEROID_COLLISION: {
		Asteroid* asteroidBroken = static_cast<const msg::BulletAsteroidCollision&>(msg).asteroid_;
		globalSend(this, msg::AsteroidDestroyed(getId(), msg::Broadcast, 4 - asteroidBroken->getGeneration()));
		if (asteroidBroken->getGeneration() > 1)
		{
			Asteroid* newAsteroid1 = this->getUnusedObject();
			newAsteroid1->setGeneration(asteroidBroken->getGeneration() - 1);
			newAsteroid1->setPosition(asteroidBroken->getPosition());
			newAsteroid1->setHeight(0.75 *asteroidBroken->getHeight());
			newAsteroid1->setWidth(0.75 *asteroidBroken->getWidth());
			newAsteroid1->setVelocity(asteroidBroken->getVelocity() * 1.1);
			newAsteroid1->setRotation(asteroidBroken->getRotation() * 30);
			newAsteroid1->setActive(true);

			Asteroid* newAsteroid2 = this->getUnusedObject();
			newAsteroid2->setGeneration(asteroidBroken->getGeneration() - 1);
			newAsteroid2->setPosition(asteroidBroken->getPosition());
			newAsteroid2->setHeight(0.75 * asteroidBroken->getHeight());
			newAsteroid2->setWidth(0.75 *asteroidBroken->getWidth());
			newAsteroid2->setVelocity(asteroidBroken->getVelocity().rotate(180) * 1.1);
			newAsteroid2->setRotation(asteroidBroken->getRotation() * 60);
			newAsteroid2->setActive(true);

		}
		asteroidBroken->setActive(false);
		if (aliveAsteroids() <= 0)
			globalSend(this, msg::Message(msg::NO_MORE_ASTEROIDS, getId(), msg::Broadcast));
		break; 
	}
	case msg::BLACKHOLE_ASTEROID_COLLISION: {

		getGame()->getServiceLocator()->getAudios()->playChannel(Resources::Wall_Hit, 0, 3); //other channel for play various sounds together
		Asteroid* asteroidBlackHoleTrip = static_cast<const msg::BlackHoleAsteroidCollision&>(msg).asteroid_;
		int height;
		int width;
		RandomNumberGenerator* r = getGame()->getServiceLocator()->getRandomGenerator();
		width = r->nextInt(0 + asteroidBlackHoleTrip->getWidth(), 800 - asteroidBlackHoleTrip->getWidth());
		height = r->nextInt(0 + asteroidBlackHoleTrip->getHeight(), 600 - asteroidBlackHoleTrip->getHeight());
		asteroidBlackHoleTrip->setPosition(Vector2D(width, height));

		AsteroidsGame* g = static_cast<AsteroidsGame*>(getGame());

		while (Collisions::collidesWithRotation(asteroidBlackHoleTrip, g->getFighter()))
		{	
			Logger::getInstance()->log([]() {
				stringstream s;
				s << "AsteoridBlackHoleTrip CollisionVsFither: " << endl;
				return s.str();
			});

			width = r->nextInt(0 + asteroidBlackHoleTrip->getWidth(), 800 - asteroidBlackHoleTrip->getWidth());
			height = r->nextInt(0 + asteroidBlackHoleTrip->getHeight(), 600 - asteroidBlackHoleTrip->getHeight());
			asteroidBlackHoleTrip->setPosition(Vector2D(width, height));
		}

		break;
	}
	}
}

 void Asteroids::colocaAsteroides(int numast)
 {
	 Asteroid* a [10];
	 RandomNumberGenerator* r = getGame()->getServiceLocator()->getRandomGenerator();
	 
	 for (int i = 0; i < numast; i++)
	 {
		 a[i] = getUnusedObject();
		 if (i<3)
		 {
			 a[i]->setPosition(Vector2D(r->nextInt(0,800-a[i]->getWidth()),0.0));
		 }
		 else if (i>=3 && i<6)
		 {
			 a[i]->setPosition(Vector2D(r->nextInt(0.0, 800-a[i]->getWidth()), 600-a[i]->getHeight()));
		 }
		 else if (i>=6 && i<8)
		 {
			 a[i]->setPosition(Vector2D(0.0, r->nextInt(0.0, 600-a[i]->getHeight())));
		 }
		 else
		 {
			 a[i]->setPosition(Vector2D(800.0-a[i]->getWidth(), r->nextInt(0, 800)));
		 }

		 a[i]->setGeneration(generations_);
		 a[i]->setWidth(20.0);
		 a[i]->setHeight(20.0);


		 Vector2D p = a[i]->getPosition();
		 Vector2D c = Vector2D(getGame()->getWindowWidth() / 2, getGame()->getWindowHeight() / 2); 
		 Vector2D v = (c - p).normalize() * (r->nextInt(1, 10) / 20.0);

		 a[i]->setVelocity(v);
		 a[i]->setActive(true);

		 //send task to Warker_ queue
		 Logger::getInstance()->log([p, v]() {
			 stringstream s;
			 s << "New asteroid: " << p << " " << v << endl;
			 return s.str();
		 });
	 }
 }
int Asteroids::aliveAsteroids()
 {
	 int contAsteroid = 0;
	 for (Asteroid*a : getAllObjects())
	 {
		 if (a->isActive())
		 {
			 contAsteroid++;
		 }
	 }
	 return contAsteroid;
 }