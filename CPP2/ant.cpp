#include "stdafx.h"
#include "ant.h"
#include "nest.h"

ant::ant(nest *nest, const ant_data ed) : entity(ed.ed)
{
	this->_nest = nest;
	_power = ed.power;
	_type = ed.type;
}

void ant::act()
{
	if (_nest->use_resources(_hunger))
		heal();
	else
		_health -= _heal_amount / 2;
}

char ant::get_type() const
{
	return _type;
}
