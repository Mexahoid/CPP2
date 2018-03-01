#include "stdafx.h"
#include "larvae.h"



larvae::larvae(queen const *q, nest *const nest) : ant(nest, nest->get_info(4))
{
	q_ = q;
}

void larvae::act()
{
	ant::act();
	power_--;
	if (power_ == 0)
		evolve();
}

void larvae::evolve()
{
	q_->ask_for_evolve();
	health_ = 0;
}
