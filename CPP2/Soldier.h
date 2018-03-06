#pragma once
#include "entities.h"
#include "nest.h"

class soldier : public ant
{
public:
	soldier(nest *nest);
	void act() override;
	static int get_revealing_chance();
	void hit_enemy(enemy *enemy) const;
};
