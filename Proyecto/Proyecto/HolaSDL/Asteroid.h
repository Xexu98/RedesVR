#pragma once
#include "Container.h"


class Asteroid : public Container
{
public:
	Asteroid();
	virtual ~Asteroid();
	void reset();
	int generation_ = 2;
	int getGeneration() {return generation_; }
	void setGeneration(int gen) {generation_ = gen; }
};

