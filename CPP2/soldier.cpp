#include "stdafx.h"
#include "soldier.h"

soldier::soldier(const int hunger, const int health, nest *nest) : ant(hunger, health, nest)
{
	type_ = 1;
	power_ = nest_->get_soldier_info();
}

void soldier::act() const
{
	nest_->use_resources(hunger_);
	nest_->clear_enemies(power_);
}
