#pragma once
#include "entities.h"
#include "enemy.h"
#include "ant.h"
#include "queen.h"

typedef struct {
	int day;
	int queen_health;
	int food_current;
	int enemies_current;

	int soldier_count;
	int overseer_count;
	int slave_count;
	int larvae_count;

} data_for_day;


class nest
{
	ant_list *entities_;
	enemy_list *enemies_;
	ant_data infos_[5];

	int food_quantity_;
	int food_max_default_;
	int food_max_;
	int enemies_count_ = 0;
	int enemies_per_soldier_ = 0;
	int day_ = 1;

public:
	explicit nest(starting_numbers numbers);
	void overseer_increase(int power);
	void overseer_decrease(int power);
	bool use_resources(int count);
	void add_resources(int count);
	ant_data get_info(char type) const;
	void clear_enemies(int amount, int *health);
	void clear_enemies(soldier *sold) const;
	void add_new_ant(ant *ent) const;
	double get_percentage(char type) const;
	bool pass_day();

	data_for_day start_day();


	~nest();
};
