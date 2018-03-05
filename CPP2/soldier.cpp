#include "stdafx.h"
#include "soldier.h"

soldier::soldier(nest *const nest) : ant(nest, nest->get_info(1))
{
}

void soldier::act()
{
	ant::act();
	if (health_ < 1)
		return;
	nest_->use_resources(hunger_);
	nest_->clear_enemies(power_, &health_);
}

