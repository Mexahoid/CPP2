#include "stdafx.h"
#include "enemy.h"
#include <cstdlib>
#include <ctime>


enemy::enemy()
{
	srand(time(nullptr));
	_damage = rand() % ENEMIES_POWER_MAX;
	_health = rand() % ENEMIES_HEALTH_MAX + 1;
	_max_health = _health;
	_heal_amount = _health / 5 + 1;
	_tapped = rand() % 101 < 50;
	_hunger = ENEMIES_HUNGER;
}

void enemy::use_res(int *value) const
{
	*value -= _hunger;
	if (*value < 0)
		*value = 0;
}

int enemy::get_reveal_chance()
{
	srand(time(nullptr));
	return rand() % 101;
}

void enemy::hit_another(entity* entity)
{
	if(!_tapped)
		entity->hit(_damage);
	tap();
}


