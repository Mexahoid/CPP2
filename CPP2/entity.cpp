#include "stdafx.h"
#include "entity.h"

// Entity спавнится с болезнью вызова

entity::~entity() = default;

entity::entity()
{
	_hunger = 0;
	_damage = 0;
	_max_health = 0;
	_health = 0;
	_heal_amount = 0;
	_tapped = true;
}

entity::entity(const entity_data data)
{
	_hunger = data.hunger;
	_max_health = data.health;
	_health = data.health;
	_heal_amount = data.healing;
	_tapped = true;
	_damage = data.damage;
}

// =============================================

void entity::hit(const int damage)
{
	_health -= damage;
}

int entity::get_damage() const
{
	return _damage;
}

void entity::heal()
{
	_health += _heal_amount;
	if (_health > _max_health)
		_health = _max_health;
}

void entity::tap()
{
	_tapped = true;
}

void entity::untap()
{
	_tapped = false;
}

// =============================================

int entity::get_health() const
{
	return _health;
}

bool entity::is_alive()
{
	return _health > 0;
}

bool entity::is_tapped() const
{
	return _tapped;
}
