#include "stdafx.h"
#include "larva.h"
#include <ctime>
#include <cstdlib>
#include <string>


larva::larva(queen const *q, nest *const nest, const bool is_inited) : ant(nest, nest->get_info(4))
{
	_q = q;
	if (is_inited)
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
		{
			if (STARVATION_DEATH_INFO)
			{
				_messenger("---------------------", true);
				_messenger("Larva died due to starvation.", true);
				_messenger("---------------------", true);
			}
			return;
		}
		_power--;
		if (_power == 0)
			evolve();
	}

	// Если загрызли в фазе атаки
	if (_health < 1)
	{
		return;
	}

	// Разрешено хилиться во второй мейн фазе, если нужно
	if (_tapped && _health <= _max_health - _heal_amount)
		ant::act();
}

void larva::evolve()
{
	if (LARVA_ASK_TO_QUEEN_INFO)
	{
		_messenger("---------------------", true);
		_messenger("Larva asked Queen for evolving, Queen has answered: ", false);
	}
	_q->ask_for_evolve();
	_health = 0;
}