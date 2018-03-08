#pragma once
#include "entities.h"
#include "entity.h"

class ant : public entity
{
protected:
	nest *_nest;
	int _power = 0;
public:
	explicit ant(nest *nest, ant_data ed);
	virtual void act();
};

