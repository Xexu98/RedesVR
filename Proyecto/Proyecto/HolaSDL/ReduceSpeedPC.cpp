#include "ReduceSpeedPC.h"



ReduceSpeedPC::ReduceSpeedPC(double factor) : factor_(factor)
{ 

}


ReduceSpeedPC::~ReduceSpeedPC()
{
}

void ReduceSpeedPC::update(Container* c, Uint32 time) 
{
	v=c->getVelocity()*factor_;
	c->setVelocity(v);
}