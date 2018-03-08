#include "stdafx.h"
#include "soldier.h"
#include <cstdlib>
#include <ctime>
#include <string>

soldier::soldier(nest *const nest) : ant(nest, nest->get_info(1))
{
	// Выходит на поле боя без болезни вызова
	entity::untap();
}

void soldier::act()
{
	// Zoldaten имеет трейт бдительности, потому не разворачивается при еде
	ant::act();
	if (_health < 1)
	{
		if (STARVATION_DEATH_INFO)
		{
			_messenger("---------------------", true);
			_messenger("Soldier died due to starvation.", true);
			_messenger("---------------------", true);
		}
		return;
	}
	if (_health <= _max_health - _heal_amount)
		ant::act();
}

int soldier::get_revealing_chance()
{
	srand(time(nullptr));
	return rand() % 101;
}
