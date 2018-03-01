#include "stdafx.h"
#include "larvae.h"
#include <ctime>
#include <cstdlib>


larvae::larvae(queen const *q, nest *const nest, bool is_inited) : ant(nest, nest->get_info(4))
{
	q_ = q;
	if(is_inited)
	{
		srand(time(nullptr));
		power_ = rand() % power_;
	}
}

void larvae::act()
{
	ant::act();
	if (health_ < 1)
		return;
	power_--;
	if (power_ == 0)
		evolve();
}

void larvae::evolve()
{
	q_->ask_for_evolve();
	health_ = 0;
}
