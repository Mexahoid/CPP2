#include "stdafx.h"
#include "enemy.h"
#include <cstdlib>
#include <ctime>


enemy::enemy() : entity(0, 0, 0)
{
	srand(time(nullptr));
	power_ = rand() % ENEMIES_POWER_MAX;
	health_ = rand() % ENEMIES_HEALTH_MAX;
	heal_amount_ = health_ / 10;
	hunger_ = ENEMIES_HUNGER;
}

