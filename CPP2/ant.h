#pragma once
#include "entities.h"
#include "entity.h"

class ant : public entity
{
protected:
	nest *nest_;
	int power_ = 0;
	char type_ = 5;
public:
	explicit ant(nest *nest, ant_data ed);
	virtual void act();
	char get_type() const;
};

