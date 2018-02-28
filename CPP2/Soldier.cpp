#include "stdafx.h"
#include "Soldier.h"

soldier::soldier(const int hunger, const int health, nest *nest) : ant(hunger, health, nest)
{
	power_ = nest_->getSoldierInfo();
}

void soldier::act() const
{
	nest_->UseResources(hunger_);
	nest_->clearEnemies(power_);
}
