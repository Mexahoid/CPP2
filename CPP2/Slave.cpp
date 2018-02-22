#include "stdafx.h"
#include "Slave.h"

Slave::Slave(int hunger, Nest *nest) : Entity(hunger, nest)
{
	power = nest->getSlaveInfo();
}

void Slave::Act()
{
	nest->UseResources(hunger);
	nest->AddResources(power);
}
