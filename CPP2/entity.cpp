#include "stdafx.h"
#include "entity.h"


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

int entity::get_health()
{
	return health_;
}