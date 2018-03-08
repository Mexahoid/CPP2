#include "stdafx.h"
#include "queen.h"
#include <ctime>
#include <cstdlib>

queen::queen(nest *const nest) : ant(nest, nest->get_info(0))
{
	_tapped = false;
}

void queen::ask_for_evolve() const
{
	char type = 1;
	double percentage[] = { 0, 0, 0 };
	for (type = 0; type < 3; type++)
	{
		percentage[type] = _nest->get_percentage(type + 1);
	}

	percentage[0] *= SOLDIER_MULT;
	percentage[1] *= OVERSEER_MULT;
	percentage[2] *= SLAVE_MULT;

	double min = 0xffffffff;
	char lesser_type = 1;
	for (type = 0; type < 3; type++)
	{
		if (percentage[type] < min)
		{
			min = percentage[type];
			lesser_type = type;
		}
	}
	switch (lesser_type + 1)
	{
	case 1:
		_nest->add_new_ant(new soldier(_nest));
		break;
	case 2:
		_nest->add_new_ant(new overseer(_nest));
		break;
	case 3:
		_nest->add_new_ant(new slave(_nest));
		break;
	default:
		break;
	}
}

void queen::act()
{
	// Если ее загрызли
	if (_health < 1)
	{
		_death_reason = false;
		return;
	}

	// Сначала попробовать поесть
	if (!_tapped)
		ant::act();
	
	// Вдруг сразу не хватило еды, надо подохнуть
	if (_health < 1)
	{
		_death_reason = true;
		return;
	}

	// Если повернута, но ХП не полное 
	// для второй мейн фазы
	if (_tapped && _health <= _max_health - _heal_amount)
		ant::act();

	// Если личинок уже больше 30%, то повернуться и выйти
	// Т.е. если в первой мейн фазе спавнить не нужно
	// А во второй мейн фазе нельзя заспавнить, если заспавнила в первой
	if (!_tapped && _nest->get_percentage(4) > 0.3)
	{
		tap();
		return;
	}

	// Если личинок меньше и она не повернута
	// Может сработать как в первой, так и во второй мейн фазе
	if (!_tapped)
	{
		srand(time(nullptr));
		const int spawning = rand() % _power;
		for (int i = 0; i < spawning; i++)
		{
			larva *lv = new larva(this, _nest);
			_nest->add_new_ant(lv);
		}
		tap();
	}
}

bool queen::get_death_reason() const
{
	return _death_reason;
}
