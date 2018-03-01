#include "stdafx.h"
#include "ant.h"
#include "Nest.h"

ant::ant(const int hunger, const int health, nest *nest)
{
	this->nest_ = nest;
	this->hunger_ = hunger;
	this->health_ = health;
}

void ant::act() const
{
	nest_->use_resources(hunger_);
}

bool ant::is_alive() const
{
	return health_ > 0;
}

char ant::get_type() const
{
	return type_;
}
