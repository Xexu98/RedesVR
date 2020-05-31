#pragma once

#include "Container.h"
#include "ImageGC.h"
#include "RotationIC.h"
#include "ThrustICP2.h"
#include "NaturalMovePC.h"
#include "ReduceSpeedPC.h"
#include "ShowUpAtOppositeSidePC.h"
#include "GunIC.h"
#include "Vector2D.h"	
#include "GunP2IC.h"



class Player2 : public Container
{

public:

	Player2(SDLGame* game);
	~Player2();

	double getPosX() { return position_.getX(); };
	double getPosY() { return position_.getY(); };
	void setPosX(double x) { position_.setX(x); };
	void setPosY(double y) { position_.setY(y); };

	virtual void receive(const void* senderObj, const msg::Message& msg);


private:
	//..
	//components
	int life = 100;
	ImageGC player2Image_;
	NaturalMovePC naturalMove_;
	ShowUpAtOppositeSidePC oppositeSide_;
	RotationIC rotation_;
	ThrustICP2 thrust_;
	ReduceSpeedPC reduceSpeed_;
	GunP2IC normalGun_;

	void reset();

};

