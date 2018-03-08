#include "stdafx.h"
#include "larva.h"
#include <ctime>
#include <cstdlib>


larva::larva(queen const *q, nest *const nest, const bool is_inited) : ant(nest, nest->get_info(4))
{
	_q = q;
	if(is_inited)
	{
		srand(time(nullptr));
		_power = rand() % _power;
	}
}

void larva::act()
{
	if (!_tapped)
	{
		ant::act();
		tap();
		if (_health < 1)
			return;
		_power--;
		if (_power == 0)
			evolve();
	}

	// Если загрызли в фазе атаки
	if (_health < 1)
		return;

	// Разрешено хилиться во второй мейн фазе, если нужно
	if (_tapped && _health <= _max_health - _heal_amount)
		ant::act();
}

void larva::evolve()
{
	_q->ask_for_evolve();
	_health = 0;
}
