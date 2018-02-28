#include "stdafx.h"
#include "Slave.h"

slave::slave(const int hunger, const int power) : ant(hunger)
{
	power_ = power;
}

void slave::act(nest *nest) const
{
	ant::act();
	nest->AddResources(power_);
}
