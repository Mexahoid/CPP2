#include "stdafx.h"
#include "soldier.h"
#include <cstdlib>
#include <ctime>

soldier::soldier(nest *const nest) : ant(nest, nest->get_info(1))
{
}

void soldier::act()
{
	ant::act();
	if (health_ < 1)
		return;
	nest_->use_resources(hunger_);
	nest_->clear_enemies(power_, &health_);
}

int soldier::get_revealing_chance()
{
	srand(time(nullptr));
	return rand() % 101;
}

void soldier::hit_enemy(enemy* enemy) const
{
	enemy->hit(power_);
}

