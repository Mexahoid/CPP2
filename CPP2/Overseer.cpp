#include "stdafx.h"
#include "overseer.h"


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
	}
}

overseer::~overseer()
{
	_nest->overseer_decrease(_power);
}
