#include "stdafx.h"
#include "Soldier.h"

Soldier::Soldier(int hunger, Nest *nest) : Entity(hunger, nest)
{
	power = nest->getSoldierInfo();
}

void Soldier::Act()
{
	nest->UseResources(hunger);
	nest->clearEnemies(power);
}