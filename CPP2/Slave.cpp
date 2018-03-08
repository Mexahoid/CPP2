#include "stdafx.h"
#include "slave.h"

slave::slave(nest *const nest) : ant(nest, nest->get_info(3))
{

}

void slave::act()
{
	if (!_tapped)
	{
		ant::act();
		_nest->add_resources(_power);
		tap();
	}
}
