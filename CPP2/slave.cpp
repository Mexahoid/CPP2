#include "stdafx.h"
#include "slave.h"

slave::slave(nest *const nest) : ant(nest, nest->get_info(3))
{
	
}

void slave::act()
{
	ant::act();
	if (health_ < 1)
		return;
	nest_->add_resources(power_);
}
