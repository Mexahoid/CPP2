#include "stdafx.h"
#include "ant.h"
#include "nest.h"

ant::ant(nest *nest, const entity_data ed)
{
	this->nest_ = nest;
	health_ = ed.health;
	max_health_ = health_;
	hunger_ = ed.hunger;
	power_ = ed.power;
	type_ = ed.type;
	heal_amount_ = ed.healing;
}

void ant::act()
{
	if (nest_->use_resources(hunger_))
		heal();
	else
		health_ -= heal_amount_ / 2;
}

bool ant::is_alive() const
{
	return health_ > 0;
}

void ant::hit(const int amount)
{
	health_ -= amount;
}

char ant::get_type() const
{
	return type_;
}

void ant::heal()
{
	health_ += heal_amount_;
	if (health_ > max_health_)
		health_ = max_health_;
}

int ant::get_health() const
{
	return health_;
}
