#include "stdafx.h"
#include "overseer.h"


overseer::overseer(const int hunger, const int health, nest *nest) : ant(hunger, health, nest)
{
	type_ = 2;
	power_ = nest_->get_overseer_info();
	nest_->overseer_increase(power_);
}

overseer::~overseer()
{
	nest_->overseer_decrease(power_);
}
