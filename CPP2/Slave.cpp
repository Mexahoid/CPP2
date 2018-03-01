#include "stdafx.h"
#include "slave.h"

slave::slave(const int hunger, const int health, nest *nest) : ant(hunger, health, nest)
{
	power_ = nest_->getSlaveInfo();
}

void slave::act() const
{
	ant::act();
	nest_->AddResources(power_);
}
