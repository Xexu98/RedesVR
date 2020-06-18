#pragma once
#include "Container.h"
#include "ImageGC.h"
#include "RotationIC.h"
#include "ThrustIC.h"
#include "NaturalMovePC.h"
#include "ReduceSpeedPC.h"
#include "ShowUpAtOppositeSidePC.h"
#include "GunIC.h"
#include "Vector2D.h"	
#include "core.h"


struct Player_Input
{
	bool32 up, down, left, right, jump;
	float32 pitch;
	float32 yaw;
};

struct Player_Snapshot_State
{
	Vector2D position;
	float32 pitch;
	float32 yaw;
};
struct Player_Extra_State
{
	Vector2D velocity;
};

class Player: public Container
{
public:
	Player(SDLGame* game);
	~Player();
	//..
	double getPosX() { return position_.getX(); };
	double getPosY() { return position_.getY(); };
	void setPosX(double x) { position_.setX(x); };
	void setPosY(double y) { position_.setY(y); };

	virtual void receive(const void* senderObj, const msg::Message& msg);


private:
	//..
	//components
	int life = 100;
	ImageGC fighterImage_;
	NaturalMovePC naturalMove_;
	ShowUpAtOppositeSidePC oppositeSide_;
	RotationIC rotation_;
	ThrustIC thrust_;
	ReduceSpeedPC reduceSpeed_;
	GunIC normalGun_;

	void reset();
};

