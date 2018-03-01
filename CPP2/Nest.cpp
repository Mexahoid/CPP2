#include "stdafx.h"
#include "nest.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

void init_infos(entity_data *infos)
{
	infos[0] = { QUEEN_HEALTH, QUEEN_HUNGER, QUEEN_POWER, 0, QUEEN_HEAL};
	infos[1] = { SOLDIER_HEALTH, SOLDIER_HUNGER, SOLDIER_POWER, 1, SOLDIER_HEAL };
	infos[2] = { OVERSEER_HEALTH, OVERSEER_HUNGER, OVERSEER_POWER, 2, OVERSEER_HEAL };
	infos[3] = { SLAVE_HEALTH, SLAVE_HUNGER, SLAVE_POWER, 3, SLAVE_HEAL };
	infos[4] = { LARVAE_HEALTH, LARVAE_HUNGER, LARVAE_TIME, 4, LARVAE_HEAL };
}

int get_fair_enemy_count()
{
	srand(time(nullptr));
	return rand() % ENEMIES_INCOME_COUNT_MAX;
}

int get_fair_enemy_power()
{
	srand(time(nullptr));
	return rand() % ENEMIES_POWER_MAX;
}

bool was_hit_successful()
{
	srand(time(nullptr));
	const auto hit_chance_threshold = rand() % 101;
	const auto hit_chance = rand() % 101;
	return hit_chance * 2 < hit_chance_threshold;
}

void print_data(const data_for_day dt)
{
	std::cout << "Day " << dt.day << std::endl;
	if(dt.queen_health > 0)
		std::cout << "Queen health: " << dt.queen_health << std::endl;
	else
	{
		std::cout << "Queen died due to: " << (dt.queen_health == -1 ? "starvation" : "enemies") << std::endl;
	}
	std::cout << "Food count: " << dt.food_current << std::endl;
	if(dt.enemies_current > -1)
	std::cout << "Enemies count: " << dt.enemies_current << std::endl;
	if (dt.soldier_count > -1)
	std::cout << "Soldiers count: "	<< dt.soldier_count << std::endl;
	if (dt.overseer_count > -1)
	std::cout << "Overseers count: " << dt.overseer_count << std::endl;
	if (dt.slave_count > -1)
	std::cout << "Slaves count: " << dt.slave_count << std::endl;
	if (dt.larvae_count > -1)
	std::cout << "Larvas count: " << dt.larvae_count << std::endl;

	std::cout << "=============================" << std::endl;
}

void init_starting(starting_numbers st, entity_list *el, nest *nest, queen *q)
{
	entity_list *p = el;
	for (int i = 0; i < st.soldier_count; i++)
	{
		while(p->next)
		{
			p = p->next;
		}

		entity_list *et = new entity_list();
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

		entity_list *et = new entity_list();
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

		entity_list *et = new entity_list();
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

		entity_list *et = new entity_list();
		et->entity = new larvae(q, nest, true);
		et->next = nullptr;
		p->next = et;
	}
}

nest::nest(const starting_numbers numbers)
{
	init_infos(infos_);
	food_max_default_ = numbers.food_max;
	food_max_ = numbers.food_max;
	food_quantity_ = numbers.food_current;

	queen * q = new queen(this);
	entities_ = new entity_list();
	entities_->entity = static_cast<ant *>(q);
	entities_->next = nullptr;

	init_starting(numbers, entities_, this, q);
}

void nest::overseer_increase(const int power)
{
	food_max_ += food_max_default_ * power / 100;
}

void nest::overseer_decrease(const int power)
{
	food_max_ -= food_max_default_ * power / 100;
}

bool nest::use_resources(const int count)
{
	if (food_quantity_ < count)
		return false;
	food_quantity_ -= count;
	return true;
}

void nest::add_resources(const int count)
{
	food_quantity_ += count;
	if (food_quantity_ > food_max_)
		food_quantity_ = food_max_;
}

entity_data nest::get_info(const char type) const
{
	return infos_[type];
}

void nest::clear_enemies(const int amount) {
	enemies_count_ -= amount;
	if (enemies_count_ < 0)
		enemies_count_ = 0;
}

void nest::add_new_ant(ant *ent) const
{
	entity_list *el = entities_;
	while (el->next)
	{
		el = el->next;
	}
	entity_list *nel = new entity_list();
	nel->entity = ent;
	nel->next = nullptr;
	el->next = nel;
}

bool nest::pass_day()
{
	data_for_day dfd{
		day_++,
		entities_->entity->get_health(),
		food_quantity_,
		enemies_count_,
		0, 0, 0, 0
	};

	entity_list *el = entities_;
	if (!el->entity->is_alive())
	{
		dfd.queen_health = dynamic_cast<queen *>(el->entity)->get_death_reason() ? -1 : -2;
		dfd.soldier_count = -1;
		dfd.slave_count = -1;
		dfd.overseer_count = -1;
		dfd.larvae_count = -1;
		dfd.enemies_current = -1;
		print_data(dfd);
		return false;
	}
	use_resources(ENEMIES_HUNGER * enemies_count_);

	while (el)
	{
		if(el->next && !el->next->entity->is_alive())
		{
			entity_list *d = el->next;
			el->next = el->next->next;
			delete d->entity;
			delete d;
		}
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
		el->entity->act();
		if(enemies_count_ && was_hit_successful())
			el->entity->hit(get_fair_enemy_power());
		el = el->next;
	}
	enemies_count_ += get_fair_enemy_count();
	print_data(dfd);
	return true;
}

double nest::get_percentage(const char type) const
{
	int count = 0;
	int needed_type_count = 0;

	entity_list *el = entities_;
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
	entity_list *el = entities_;
	while (el)
	{
		entity_list *d = el;
		el = el->next;
		delete d->entity;
		delete d;
	}
	delete el;
}
