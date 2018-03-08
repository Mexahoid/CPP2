#include "stdafx.h"
#include "entity.h"
#include "consts.h"

// Entity спавнится с болезнью вызова

entity::~entity() = default;

void entity::send_hit_message(char type, int damage) const
{
	if (FIGHT_INFO)
	{
		const char *name;
		switch (type)
		{
		case 0:
			name = "Queen";
			if (!QUEEN_HIT_INFO)
				return;
			break;
		case 1:
			name = "Soldier";
			break;
		case 2:
			name = "Overseer";
			if (!OVERSEER_HIT_INFO)
				return;
			break;
		case 3:
			name = "Slave";
			if (!SLAVE_FIGHT_INFO)
				return;
			break;
		case 4:
			name = "Larva";
			if (!LARVA_HIT_INFO)
				return;
			break;
		default:
			name = "Enemy";
			if (!ENEMY_HIT_INFO)
				return;
			break;
		}
		//_messenger("---------------------", true);
		_messenger(name, false);
		_messenger(" got hit for ", false);
		_messenger(std::to_string(damage).c_str(), false);
		_messenger(" damage.", true);
		_messenger("Current health: ", false);
		_messenger(std::to_string(_health).c_str(), false);
		_messenger(" hp.", true);
		//_messenger("---------------------", true);
		if (_health < 1)
		{
			_messenger(name, false);
			_messenger(" was slain.", true);
		}
	}
}
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
	send_hit_message(_type, damage);
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

char entity::get_type() const
{
	return _type;
}
