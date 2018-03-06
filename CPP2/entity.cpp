#include "stdafx.h"
#include "entity.h"


entity::entity()
{
	hunger_ = 0;
	max_health_ = 0;
	health_ = 0;
	heal_amount_ = 0;
}

entity::entity(const int health, const int hunger, const int healing)
{
	hunger_ = hunger;
	max_health_ = health;
	health_ = health;
	heal_amount_ = healing;
}

void entity::hit(const int damage)
{
	health_ -= damage;
}

void entity::heal()
{
	health_ += heal_amount_;
	if (health_ > max_health_)
		health_ = max_health_;
}

int entity::get_health() const
{
	return health_;
}

bool entity::is_alive()
{
	return health_ > 0;
}

void entity::turn()
{
	turned_ = !turned_;
}

bool entity::is_turned() const
{
	return turned_;
}