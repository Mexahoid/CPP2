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
	explicit ant(nest *nest, entity_data ed);
	virtual void act();
	bool is_alive() const;
	char get_type() const;
};

