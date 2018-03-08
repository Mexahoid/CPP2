#pragma once
#include "entities.h"
#include "enemy.h"
#include "ant.h"
#include "queen.h"

typedef struct {
	int day;
	int queen_health;
	int food_current;

	int soldier_count;
	int overseer_count;
	int slave_count;
	int larvae_count;

} data_for_day;


class nest
{
	ant_list *_entities;
	ant_data _infos[5];

	int _food_quantity;
	int _food_max_default;
	int _food_max;
	int _enemies_count = 0;
	int _enemies_per_soldier = 0;
	int _day = 0;

public:
	explicit nest(starting_numbers numbers);
	void overseer_increase(int power);
	void overseer_decrease(int power);
	bool use_resources(int count);
	void add_resources(int count);
	ant_data get_info(char type) const;
	void add_new_ant(ant *ent) const;
	double get_percentage(char type) const;

	void act() const;
	data_for_day collect_data() const;

	void untap_all();
	void clear_dead() const;
	void get_attack(enemy *enemy);

	~nest();
};
