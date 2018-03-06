#include "stdafx.h"
#include "world.h"
#include "nest.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

void world::incr_enemies(const int count)
{
	enemy_list *el = enemies_;
	for (int i = 0; i < count; i++)
	{
		enemy_list *nel = new enemy_list();
		nel->enemy = new enemy();
		nel->next = nullptr;
		if (!enemies_)
		{
			enemies_ = nel;
			el = nel;
		}
		else
		{
			while (el->next)
			{
				el = el->next;
			}
			el->next = nel;
		}
		el = el->next;
	}
}

void delete_next(enemy_list *enml)
{
	if (!enml->next)
		return;

	enemy_list *dlt = enml->next;
	if (enml->next->next)
	{
		enml->next = enml->next->next;
	}
	else
	{
		enml->next = nullptr;
	}
	if (dlt->enemy)
		delete dlt->enemy;
	delete dlt;
}

void print_data(data_for_day *dt, const bool upkeep = true)
{
	const char *starting = upkeep ? "Start of the day " : "End of the day ";
	std::cout << starting << dt->day << std::endl;
	if (dt->queen_health > 0)
		std::cout << "Queen health: " << dt->queen_health << std::endl;
	else
	{
		std::cout << "Queen died due to: " << (dt->queen_health == -1 ? "starvation" : "enemies") << std::endl;
	}
	std::cout << "Food count: " << dt->food_current << std::endl;
	if (dt->enemies_current > -1)
		std::cout << "Enemies count: " << dt->enemies_current << std::endl;
	if (dt->soldier_count > -1)
		std::cout << "Soldiers count: " << dt->soldier_count << std::endl;
	if (dt->overseer_count > -1)
		std::cout << "Overseers count: " << dt->overseer_count << std::endl;
	if (dt->slave_count > -1)
		std::cout << "Slaves count: " << dt->slave_count << std::endl;
	if (dt->larvae_count > -1)
		std::cout << "Larvas count: " << dt->larvae_count << std::endl;

	std::cout << "=============================" << std::endl;

}

void world::clear_enemy_list()
{
	enemy_list *enml = enemies_;

	if (!enml->enemy->is_alive())
	{
		if (enemies_->next)
			enemies_ = enemies_->next;
		else
			enemies_ = nullptr;
		delete enml->enemy;
		delete enml;

		enml = enemies_;
	}

	while (enml->next)
	{
		if (!enml->enemy->is_alive())
			delete_next(enml);
		enml = enml->next;
	}
}


void world::first_main_phase()
{
	srand(time(nullptr));
	const int income = rand() % ENEMIES_INCOME_COUNT_MAX;
	incr_enemies(income);

}

void world::attack_phase()
{
}

void world::second_main_phase()
{
}


world::world(const starting_numbers st)
{
	nest_ = new nest(st);
	enemies_ = new enemy_list();
	enemies_->enemy = nullptr;
	enemies_->next = nullptr;
}

void world::pass_day()
{

}


world::~world()
{
	delete nest_;
	delete enemies_;
}
