#include "stdafx.h"
#include "overseer.h"


overseer::overseer(const int hunger, const int health, nest *nest) : ant(hunger, health, nest)
{
	nest_->overseer_increase(power_);
}

overseer::~overseer()
{

}
