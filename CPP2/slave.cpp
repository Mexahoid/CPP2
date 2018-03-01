#include "stdafx.h"
#include "slave.h"

slave::slave(const int hunger, const int health, nest *nest) : ant(hunger, health, nest)
{
	type_ = 3;
	power_ = nest_->get_slave_info();
}

void slave::act() const
{
	ant::act();
	nest_->add_resources(power_);
}
