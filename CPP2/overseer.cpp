#include "stdafx.h"
#include "overseer.h"


overseer::overseer(nest *const nest) : ant(nest, nest->get_info(2))
{
	nest_->overseer_increase(power_);
}

void overseer::act()
{
	ant::act();
}

overseer::~overseer()
{
	nest_->overseer_decrease(power_);
}
