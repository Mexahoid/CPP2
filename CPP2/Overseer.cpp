#include "stdafx.h"
#include "Overseer.h"


overseer::overseer(const int hunger, const int health, nest *nest) : ant(hunger, health, nest)
{
	nest->overseer_increase(power);
}

overseer::~overseer()
{

}
