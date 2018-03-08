#include "stdafx.h"
#include "world.h"
#include "nest.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

void print_data(data_for_day dt, const bool upkeep = true)
{
	std::cout << "=============================";
	if (upkeep)
		std::cout << "============================";
	std::cout << std::endl;
	const char *starting = upkeep ? "Start of the day " : "End of the day ";
	std::cout << starting << dt.day << std::endl;
	if (dt.queen_health > 0)
		std::cout << "Queen health: " << dt.queen_health << std::endl;
	else
	{
		std::cout << "Queen died due to: " << (dt.queen_health == -1 ? "starvation" : "enemies") << std::endl;
	}
	std::cout << "Food count: " << dt.food_current << std::endl;
	if (dt.soldier_count > -1)
		std::cout << "Soldiers count: " << dt.soldier_count << std::endl;
	if (dt.overseer_count > -1)
		std::cout << "Overseers count: " << dt.overseer_count << std::endl;
	if (dt.slave_count > -1)
		std::cout << "Slaves count: " << dt.slave_count << std::endl;
	if (dt.larvae_count > -1)
		std::cout << "Larvae count: " << dt.larvae_count << std::endl;

	std::cout << "=============================";
		if (!upkeep)
			std::cout << "============================";
	std::cout << std::endl;

}

void print_info(const char *text, bool add_endl)
{
	std::cout << text;
	if (add_endl)
		std::cout << std::endl;
}

void delete_next_dead_enemies(enemy_list *enml)
{
	enemy_list *ptr = enml->next;
	while (ptr->next && !ptr->next->enemy->is_alive())
	{
		if (ptr->next->next)
		{
			enemy_list *al = ptr->next;
			ptr->next = ptr->next->next;
			delete al->enemy;
			delete al;
		}
		else
		{
			delete ptr->next->enemy;
			delete ptr->next;
			ptr->next = nullptr;
		}
	}
}


void world::incr_enemies(int count)
{
	enemy_list *el = _enemies;
	if (!el)
	{
		count--;
		enemy_list *nel = new enemy_list();
		nel->enemy = new enemy(print_info);
		nel->next = nullptr;
		_enemies = nel;
		el = _enemies;
	}
	while(el->next)
	{
		el = el->next;
	}
	for (int i = 0; i < count; i++)
	{
		enemy_list *nel = new enemy_list();
		nel->enemy = new enemy(print_info);
		nel->next = nullptr;
		el->next = nel;
		el = el->next;
	}
}


void world::clear_enemy_list()
{
	enemy_list *enml = _enemies;

	if (!enml)
		return;

	if (!enml->enemy->is_alive())
	{
		if (_enemies->next)
			_enemies = _enemies->next;
		else
			_enemies = nullptr;
		delete enml->enemy;
		delete enml;

		enml = _enemies;
	}
	if (!enml)
		return;
	while (enml->next)
	{
		if (!enml->enemy->is_alive())
			delete_next_dead_enemies(enml);
		enml = enml->next;
	}
}


bool world::first_main_phase()
{
	clear_enemy_list();
	untap_all();
	_nest->untap_all();
	_nest->clear_dead();
	data_for_day dfd = _nest->collect_data();
	int h = dfd.queen_health;
	print_data(dfd);
	if (h < 1)
	{
		return false;
	}
	_nest->act();

	srand(time(nullptr));
	const int income = rand() % ENEMIES_INCOME_COUNT_MAX;
	incr_enemies(income);
	return true;
}

void world::attack_phase() const
{
	enemy_list *el = _enemies;
	while (el)
	{
		if (!el->enemy->is_tapped())
		{
			_nest->get_attack(el->enemy);
		}
		el = el->next;
	}
}

bool world::second_main_phase() const
{
	_nest->act();
	const data_for_day dfd = _nest->collect_data();
	int h = dfd.queen_health;
	print_data(dfd, false);
	return h >= 1;
}


world::world(const starting_numbers st)
{
	_nest = new nest(st, print_info);
	_enemies = nullptr;
}

bool world::pass_day()
{
	if (!first_main_phase())
	{
		return false;
	}
	attack_phase();
	return second_main_phase();
}


world::~world()
{
	delete _nest;
	delete _enemies;
}

void world::untap_all() const
{
	enemy_list *el = _enemies;
	while (el)
	{
		if (el->next && !el->next->enemy->is_alive())
		{
			delete_next_dead_enemies(el);
		}
		el->enemy->untap();
		el = el->next;
	}
}
