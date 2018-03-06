#pragma once
#include "entities.h"
#include "entity.h"

class enemy : public entity
{
	int power_;
public:
	enemy();
	int get_hunger() const;
	int get_power() const;
	void use_res(int *value) const;
	static int get_reveal_chance();
	virtual void hit_another(entity *entity);
};

