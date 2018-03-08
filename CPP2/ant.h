#pragma once
#include "entities.h"
#include "entity.h"

class ant : public entity
{
protected:
	nest *_nest;
	int _power = 0;
	char _type = 5;
public:
	explicit ant(nest *nest, ant_data ed);
	virtual void act();
	char get_type() const;
};

