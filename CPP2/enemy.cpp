#include "stdafx.h"
#include "enemy.h"
#include <cstdlib>
#include <ctime>
#include "ant.h"


enemy::enemy(messenger messenger)
{
	_messenger = messenger;
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
	if (ENEMY_STEALING_INFO)
	{
		_messenger("---------------------", true);
		_messenger("Enemy has stolen ", false);
		_messenger(std::to_string(_hunger).c_str(), false);
		_messenger(" food.", true);
		_messenger("---------------------", true);
	}
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
	if (!_tapped)
		entity->hit(_damage);
	tap();
}


