#pragma once
#include "entities.h"
#include "entity.h"

class enemy : public entity
{
public:
	enemy();
	void use_res(int *value) const;
	static int get_reveal_chance();
	virtual void hit_another(entity *entity);
};

