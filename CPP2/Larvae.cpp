#include "stdafx.h"
#include "Larvae.h"
#include "Nest.h"


larvae::larvae(const int hunger, const int health, int (*queen_method)(), nest *nest) : ant(hunger, health, nest)
{
	ask_queen_for_evolving_ = queen_method;
	time_before_evolving_ = LARVAE_TIME;
}

void larvae::act()
{
	nest_->UseResources(hunger_);
	time_before_evolving_--;
	if (time_before_evolving_ == 0)
		evolve();
}

void larvae::evolve()
{
	ask_queen_for_evolving_();
	health_ = 0;
}
