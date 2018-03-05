#include "stdafx.h"
#include "enemy.h"
#include <cstdlib>
#include <ctime>


enemy::enemy()
{
	srand(time(nullptr));
	power_ = rand() % ENEMIES_POWER_MAX;
	health_ = rand() % ENEMIES_HEALTH_MAX;
	heal_amount_ = health_ / 10;
	hunger_ = ENEMIES_HUNGER;
}

int enemy::get_hunger() const
{
	return hunger_;
}

int enemy::get_power() const
{
	return power_;
}

void enemy::use_res(int *value) const
{
	*value -= hunger_;
	if (*value < 0)
		*value = 0;
}

int enemy::get_reveal_chance()
{
	srand(time(nullptr));
	return rand() % 101;
}

