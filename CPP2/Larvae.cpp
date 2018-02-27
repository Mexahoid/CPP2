#include "stdafx.h"
#include "Larvae.h"
#include "Nest.h"


larvae::larvae(const int hunger, int (*queen_method)(), Nest *nest) : ant(hunger, nest)
{
	queen_api_ = queen_method;
	time_before_evolving_ = LARVAE_TIME;
}

void larvae::act()
{
	nest_->UseResources(hunger_);
	time_before_evolving_--;
	if (time_before_evolving_ == 0)
		evolve();
}

void larvae::evolve() const
{
	queen_api_();
}
