#include "stdafx.h"
#include "ant.h"
#include "nest.h"

ant::ant(nest *nest, const entity_data ed) : entity(ed.health, ed.hunger, ed.healing)
{
	this->nest_ = nest;
	power_ = ed.power;
	type_ = ed.type;
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

char ant::get_type() const
{
	return type_;
}
