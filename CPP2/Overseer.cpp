#include "stdafx.h"
#include "overseer.h"
#include <string>


overseer::overseer(nest *const nest) : ant(nest, nest->get_info(2))
{
	_nest->overseer_increase(_power);
}

void overseer::act()
{
	if (!_tapped)
	{
		ant::act();
		tap(); 
		if (_health < 1)
		{
			_messenger("---------------------", true);
			_messenger("Overseer died due to starvation.", true);
			_messenger("---------------------", true);
		}
	}
}

overseer::~overseer()
{
	_nest->overseer_decrease(_power);
}
