#include "stdafx.h"
#include "nest.h"
#include <cstdlib>
#include <ctime>
#include <iostream>


void init_infos(ant_data *infos)
{
	infos[0] = { QUEEN_HEALTH, QUEEN_HUNGER, QUEEN_POWER, 0, QUEEN_HEAL };
	infos[1] = { SOLDIER_HEALTH, SOLDIER_HUNGER, SOLDIER_POWER, 1, SOLDIER_HEAL };
	infos[2] = { OVERSEER_HEALTH, OVERSEER_HUNGER, OVERSEER_POWER, 2, OVERSEER_HEAL };
	infos[3] = { SLAVE_HEALTH, SLAVE_HUNGER, SLAVE_POWER, 3, SLAVE_HEAL };
	infos[4] = { LARVAE_HEALTH, LARVAE_HUNGER, LARVAE_TIME, 4, LARVAE_HEAL };
}


bool was_hit_successful(const bool is_enemy)
{
	srand(time(nullptr));
	const auto hit_chance_threshold = rand() % 101;
	const auto hit_chance = rand() % 101;
	const int mult = is_enemy ? 1 : 3;
	return hit_chance * mult > hit_chance_threshold;
}

void fight(entity *victim, enemy *enemy)
{
	
	if(was_hit_successful(true))
	{
		enemy->hit_another(victim);
	}

	if(static_cast<ant *>(victim)->get_type() == 1 && was_hit_successful(false))
	{
		static_cast<soldier *>(victim)->hit_enemy(enemy);
	}
}

bool decrease_quantity(int amount, int *value)
{
	if (*value < amount)
		return false;
	*value -= amount;
	return true;
}

void print_data(const data_for_day dt)
{
	std::cout << "Day " << dt.day << std::endl;
	if (dt.queen_health > 0)
		std::cout << "Queen health: " << dt.queen_health << std::endl;
	else
	{
		std::cout << "Queen died due to: " << (dt.queen_health == -1 ? "starvation" : "enemies") << std::endl;
	}
	std::cout << "Food count: " << dt.food_current << std::endl;
	if (dt.enemies_current > -1)
		std::cout << "Enemies count: " << dt.enemies_current << std::endl;
	if (dt.soldier_count > -1)
		std::cout << "Soldiers count: " << dt.soldier_count << std::endl;
	if (dt.overseer_count > -1)
		std::cout << "Overseers count: " << dt.overseer_count << std::endl;
	if (dt.slave_count > -1)
		std::cout << "Slaves count: " << dt.slave_count << std::endl;
	if (dt.larvae_count > -1)
		std::cout << "Larvas count: " << dt.larvae_count << std::endl;

	std::cout << "=============================" << std::endl;
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
	entities_ = new ant_list();
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
	return decrease_quantity(count, &food_quantity_);
}

void nest::add_resources(const int count)
{
	food_quantity_ += count;
	if (food_quantity_ > food_max_)
		food_quantity_ = food_max_;
}

ant_data nest::get_info(const char type) const
{
	return infos_[type];
}

void nest::clear_enemies(const int soldier_power, int *health) {

	if (enemies_count_ != 0)
		for (int i = 0; i < enemies_per_soldier_; i++)
		{
			if (was_hit_successful(true))
			{
				const int enemy_power = get_fair_enemy_power();
				if (enemy_power > soldier_power)
					*health -= enemy_power;
			}
			if (*health < 1)
				return;
			if (was_hit_successful(false))
			{
				enemies_count_--;
				if (enemies_count_ < 0)
				{
					enemies_count_ = 0;
					break;
				}
			}
		}
}

void nest::clear_enemies(soldier* sold) const
{
	if (enemies_count_ != 0)
	{
		enemy_list *el = enemies_;
		for (int i = 0; i < enemies_per_soldier_; i++)
		{
			while(el && el->enemy->is_turned())
			{
				el = el->next;
			}
			if (el)
			{
				fight(sold, el->enemy);
			}
			else
				return;
		}
	}
}

void nest::add_new_ant(ant *ent) const
{
	ant_list *el = entities_;
	while (el->next)
	{
		el = el->next;
	}
	ant_list *nel = new ant_list();
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



	ant_list *el = entities_;
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

	enemy_list *enl = enemies_;
	// int revealing_chance
	while(enl)
	{
		int reveal_chance = enl->enemy->get_reveal_chance();

		enl->enemy->use_res(&food_quantity_);
		enl = enl->next;
	}

	use_resources(ENEMIES_HUNGER * enemies_count_);

	while (el)
	{
		if (el->entity->get_type() == 1)
			dfd.soldier_count++;
		el = el->next;
	}

	if(dfd.soldier_count)
		enemies_per_soldier_ = enemies_count_ / dfd.soldier_count + 1;

	el = entities_;
	while (el)
	{
		if (el->next && !el->next->entity->is_alive())
		{
			ant_list *d = el->next;
			el->next = el->next->next;
			delete d->entity;
			delete d;
		}
		switch (el->entity->get_type())
		{
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
		el = el->next;
	}
	dfd.enemies_current = enemies_count_;
	print_data(dfd);
	return true;
}

data_for_day nest::start_day()
{
	data_for_day dfd{
		day_++,					
		entities_->entity->get_health(),
		food_quantity_,
		enemies_count_,
		enemies_count_,
		0, 0, 0, 0
	};


	return dfd;
}

double nest::get_percentage(const char type) const
{
	int count = 0;
	int needed_type_count = 0;

	ant_list *el = entities_;
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
	ant_list *el = entities_;
	while (el)
	{
		ant_list *d = el;
		el = el->next;
		delete d->entity;
		delete d;
	}
	delete el;
}
