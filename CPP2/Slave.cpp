#include "stdafx.h"
#include "Slave.h"

slave::slave(const int hunger, const int power) : ant(hunger)
{
	power_ = power;
}

void slave::act(Nest *nest) const
{
	ant::act(nest);
	nest->AddResources(power_);
}
