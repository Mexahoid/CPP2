#include "stdafx.h"
#include "nest.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <list>


void init_infos(ant_data *infos)
{
	infos[0] = {
		entity_data {
			QUEEN_HEALTH,
			QUEEN_HEAL,
			QUEEN_HUNGER,
			QUEEN_DAMAGE
		},
		QUEEN_POWER,
		0
	};
	infos[1] = {
		entity_data {
			SOLDIER_HEALTH,
			SOLDIER_HEAL,
			SOLDIER_HUNGER,
			SOLDIER_DAMAGE
		},
		SOLDIER_DAMAGE,
		1
	};
	infos[2] = {
		entity_data {
			OVERSEER_HEALTH,
			OVERSEER_HEAL,
			OVERSEER_HUNGER,
			OVERSEER_DAMAGE
		},
		OVERSEER_POWER,
		2,
	};
	infos[3] = {
		entity_data {
			SLAVE_HEALTH,
			SLAVE_HEAL,
			SLAVE_HUNGER,
			SLAVE_DAMAGE
		},
		SLAVE_POWER,
		3
	};
	infos[4] = {
		entity_data {
			LARVA_HEALTH,
			LARVA_HEAL,
			LARVA_HUNGER,
			LARVA_DAMAGE
		},
		LARVA_TIME,
		4
	};
}

bool was_hit_successful(const bool is_enemy)
{
	srand(time(nullptr));
	const auto hit_chance_threshold = rand() % 101;
	const auto hit_chance = rand() % 101;
	const int mult = is_enemy ? 1 : 3;
	return hit_chance * mult > hit_chance_threshold;
}

const char *get_name(char type)
{
	const char *name;
	switch (type)
	{
	case 0:
		name = "Queen";
		break;
	case 1:
		name = "Soldier";
		break;
	case 2:
		name = "Overseer";
		break;
	case 3:
		name = "Slave";
		break;
	case 4:
		name = "Larva";
		break;
	default:
		name = "Enemy";
		break;
	}
	return name;
}

void fight(entity *victim, enemy *enemy, messenger messenger)
{
	const char *name = get_name(victim->get_type());
	if (FIGHT_INFO && TWOHEADED_FIGHT_INFO)
	{
		messenger("---------------------", true);
		messenger("Fight between: ", true);
		messenger(name, false);
		messenger(" - ", false);
		messenger(std::to_string(victim->get_health()).c_str(), false);
		messenger(" hp., ", false);
		messenger(std::to_string(victim->get_damage()).c_str(), false);
		messenger(" dmg. and Enemy - ", false);
		messenger(std::to_string(enemy->get_health()).c_str(), false);
		messenger(" hp., ", false);
		messenger(std::to_string(enemy->get_damage()).c_str(), false);
		messenger(" dmg. started.", true);
	}

	srand(time(nullptr));
	const bool first_hit_for_enemy = rand() % 101 < 40;
	if (FIGHT_INFO && TWOHEADED_FIGHT_INFO)
	{
		if (first_hit_for_enemy)
			messenger("First turn for Enemy", true);
		else
		{
			messenger("First turn for ", false);
			messenger(name, true);
		}
		messenger("...............", true);
	}

	bool messaged = false;
	if (first_hit_for_enemy)
		if (was_hit_successful(true))
		{
			if (FIGHT_INFO && TWOHEADED_FIGHT_INFO)
				messenger("Enemy hit successful.", true);
			enemy->hit_another(victim);
			if (FIGHT_INFO && TWOHEADED_FIGHT_INFO)
				messenger("...............", true);
			messaged = true;
		}
		else
			if (FIGHT_INFO && TWOHEADED_FIGHT_INFO)
				messenger("Enemy missed.", true);

	if (victim->is_alive())
		if (was_hit_successful(false))
		{
			if (FIGHT_INFO && TWOHEADED_FIGHT_INFO)
			{
				messenger(name, false);
				messenger(" hit successful.", true);
			}
			enemy->hit(victim->get_damage());
			if (FIGHT_INFO && TWOHEADED_FIGHT_INFO)
				messenger("...............", true);
			messaged = true;
			victim->tap();
		}
		else
		{
			if (FIGHT_INFO && TWOHEADED_FIGHT_INFO)
			{
				messenger(name, false);
				messenger(" missed.", true);
			}
		}

	if (!first_hit_for_enemy && enemy->is_alive())
	{
		if (was_hit_successful(true))
		{
			if (FIGHT_INFO && TWOHEADED_FIGHT_INFO)
				messenger("Enemy hit successful.", true);
			enemy->hit_another(victim);
			messaged = true;
		}
		else
			if (FIGHT_INFO && TWOHEADED_FIGHT_INFO)
				messenger("Enemy missed.", true);
		if (FIGHT_INFO && TWOHEADED_FIGHT_INFO)
			messenger("...............", true);
	}
	if (FIGHT_INFO && TWOHEADED_FIGHT_INFO)
	{
		if (!messaged)
			messenger("Both hits missed.", true);
		messenger("---------------------", true);
	}
}

bool decrease_quantity(int amount, int *value)
{
	if (*value < amount)
		return false;
	*value -= amount;
	return true;
}

void init_starting(const starting_numbers st, ant_list *el, nest *nest, queen *q)
{
	ant_list *p = el;
	for (int i = 0; i < st.soldier_count; i++)
	{
		while (p->next)
		{
			p = p->next;
		}

		ant_list *et = new ant_list();
		et->entity = new soldier(nest);
		et->next = nullptr;
		p->next = et;
	}

	for (int i = 0; i < st.overseer_count; i++)
	{
		while (p->next)
		{
			p = p->next;
		}

		ant_list *et = new ant_list();
		et->entity = new overseer(nest);
		et->next = nullptr;
		p->next = et;
	}

	for (int i = 0; i < st.slave_count; i++)
	{
		while (p->next)
		{
			p = p->next;
		}

		ant_list *et = new ant_list();
		et->entity = new slave(nest);
		et->next = nullptr;
		p->next = et;
	}

	for (int i = 0; i < st.larvae_count; i++)
	{
		while (p->next)
		{
			p = p->next;
		}

		ant_list *et = new ant_list();
		et->entity = new larva(q, nest, true);
		et->next = nullptr;
		p->next = et;
	}
}

void delete_next_dead_ants(ant_list *prev)
{
	ant_list *ptr = prev;

	while (ptr->next && !ptr->next->entity->is_alive())
	{
		if (ptr->next->next)
		{
			ant_list *al = ptr->next;
			ptr->next = ptr->next->next;
			delete al->entity;
			delete al;
		}
		else
		{
			delete ptr->next->entity;
			delete ptr->next;
			ptr->next = nullptr;
		}
	}

}

void fight_random(ant_list *entities, enemy *enemy, messenger messenger)
{
	srand(time(nullptr));
	int victim_type = rand() % 5;
	ant_list *al = entities;
	while (al)
	{
		if (al->entity->get_type() == victim_type)
		{
			if (FIGHT_INFO && TWOHEADED_FIGHT_INFO)
			{
				messenger("Enemy has attacked ", false);
				messenger(get_name(victim_type), true);
			}
			bool doonce = true;
			if (victim_type == 1)
				if (FIGHT_INFO && TWOHEADED_FIGHT_INFO)
				{
					messenger("Soldier will attack Enemy 'till one of them dies.", true);
				}
			while (doonce)
			{
				if (victim_type != 1)
					doonce = false;
				if (enemy->is_alive())
					fight(al->entity, enemy, messenger);
				else
					doonce = false;
			}

			break;
		}
		al = al->next;
	}
}

bool soldier_reveal(ant_list *ants, enemy *enemy, messenger messenger)
{
	ant_list *al = ants;
	int type = al->entity->get_type();

	// »щем нетапнутого солдата
	while (al && (type != 1 || type == 1 && al->entity->is_tapped()))
	{
		al = al->next;
		if (al)
			type = al->entity->get_type();
	}
	if (al)
	{
		fight(al->entity, enemy, messenger);
		return true;
	}
	if(FIGHT_INFO && TWOHEADED_FIGHT_INFO)
	{
		messenger("All Soldiers are tired. This Enemy saved its life. But not for long..", true);
		messenger("*********************", true);
	}
	return false;
}

nest::nest(const starting_numbers numbers, const messenger messenger)
{
	_messenger = messenger;
	init_infos(_infos);
	_food_max_default = numbers.food_max;
	_food_max = numbers.food_max;
	_food_quantity = numbers.food_current;

	queen * q = new queen(this);
	_entities = new ant_list();
	_entities->entity = q;
	_entities->next = nullptr;

	init_starting(numbers, _entities, this, q);
}

void nest::overseer_increase(const int power)
{
	_food_max += _food_max_default * power / 100;
}

void nest::overseer_decrease(const int power)
{
	_food_max -= _food_max_default * power / 100;
}

bool nest::use_resources(const int count)
{
	return decrease_quantity(count, &_food_quantity);
}

void nest::add_resources(const int count)
{
	_food_quantity += count;
	if (_food_quantity > _food_max)
		_food_quantity = _food_max;
}

ant_data nest::get_info(const char type) const
{
	return _infos[type];
}


void nest::add_new_ant(ant *ent) const
{
	ant_list *el = _entities;
	while (el->next)
	{
		el = el->next;
	}
	ant_list *nel = new ant_list();
	nel->entity = ent;
	nel->next = nullptr;
	el->next = nel;
}

void nest::act() const
{
	ant_list *el = _entities;

	while (el)
	{
		el->entity->act();
		el = el->next;
	}
}

data_for_day nest::collect_data() const
{
	data_for_day dfd{
		_day,								// Day
		_entities->entity->get_health(),    // Queen health
		_food_quantity,						// Overall food count
		0,		// Soldiers
		0,		// Overseers
		0,		// Slaves
		0		// Larvae
	};

	ant_list *el = _entities;

	if (!el->entity->is_alive())
	{
		dfd.queen_health = dynamic_cast<queen *>(el->entity)->get_death_reason() ? -1 : -2;
		dfd.soldier_count = -1;
		dfd.slave_count = -1;
		dfd.overseer_count = -1;
		dfd.larvae_count = -1;
		return dfd;
	}

	while (el)
	{
		switch (el->entity->get_type())
		{
		case 1:
			dfd.soldier_count++;
			break;
		case 2:
			dfd.overseer_count++;
			break;
		case 3:
			dfd.slave_count++;
			break;
		case 4:
			dfd.larvae_count++;
			break;
		default:
			break;
		}
		el = el->next;
	}

	return dfd;
}

void nest::untap_all()
{
	_day++;
	ant_list *al = _entities;
	while (al)
	{
		al->entity->untap();
		al = al->next;
	}
}

void nest::clear_dead() const
{
	ant_list *al = _entities;
	while (al)
	{
		if (al->next && !al->next->entity->is_alive())
			delete_next_dead_ants(al);
		al = al->next;
	}
}

void nest::get_attack(enemy* enemy)
{
	ant_list *al = _entities;

	srand(time(nullptr));
	const int chance_enemy = rand() % 101;
	const int chance_victim = rand() % 101;
	const bool for_food = rand() % 101 < 50;
	int type = -1;
	if (for_food)
	{
		if (soldier::get_revealing_chance() > enemy::get_reveal_chance())
		{
			if (FIGHT_INFO && TWOHEADED_FIGHT_INFO)
				_messenger("Enemy tried to steal food. It was revealed by lurking Soldier.", true);
			soldier_reveal(_entities, enemy, _messenger);
		}
		else
		{
			enemy->use_res(&_food_quantity);
			enemy->tap();
		}
	}
	else
		if (chance_enemy > chance_victim)
		{
			fight_random(_entities, enemy, _messenger);

			if (enemy->is_alive())
				if (soldier::get_revealing_chance() * 2 > enemy::get_reveal_chance())
				{
					if (FIGHT_INFO && TWOHEADED_FIGHT_INFO)
					{
						_messenger("Previous fight was revealed by guardian Soldiers.", true);
						_messenger("Soldiers are going to attack an invader.", true);
					}
					while (enemy->is_alive())
						if(!soldier_reveal(_entities, enemy, _messenger))
							break;
					if(enemy->is_alive())
						fight_random(_entities, enemy,  _messenger);
				}
		}
		else
		{
			if (FIGHT_INFO && TWOHEADED_FIGHT_INFO)
			{
				const bool no_lore = rand() % 101 < 50;
				_messenger(no_lore ?
					"Enemy has attacked random Soldier." :
					"Soldier has attacked lurking Enemy.", true);
			}
			soldier_reveal(_entities, enemy, _messenger);
			if (enemy->is_alive())
			{
				fight_random(_entities, enemy, _messenger);
			}
		}
}

messenger nest::get_messenger() const
{
	return _messenger;
}


double nest::get_percentage(const char type) const
{
	int count = 0;
	int needed_type_count = 0;

	ant_list *el = _entities;
	while (el)
	{
		count++;
		if (el->entity->get_type() == type)
			needed_type_count++;
		el = el->next;
	}

	return needed_type_count * 1.0 / count;
}

nest::~nest()
{
	ant_list *el = _entities;
	while (el)
	{
		ant_list *d = el;
		el = el->next;
		delete d->entity;
		delete d;
	}
	delete el;
}
