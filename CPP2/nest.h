#pragma once
#include "entities.h"
#include "ant.h"
#include "queen.h"


class nest
{
private:
	entity_list *entities_;

	int food_quantity_;

	int food_max_default_;
	int food_max_;

	int enemies_count_ = 0;

	int queen_power_ = QUEEN_POWER;
	int soldier_power_ = SOLDIER_POWER;
	int overseer_power_ = OVERSEER_POWER;
	int slave_power_ = SLAVE_POWER;

public:
	explicit nest(int max);
	void overseer_increase(int power);
	void overseer_decrease(int power);
	void add_entity(ant *entity);
	void use_resources(int count);
	void add_resources(int count);
	int get_slave_info() const;
	int get_soldier_info() const;
	int get_overseer_info() const;
	int get_queen_info() const;
	void clear_enemies(int amount);
	void replace_larva_with_new_entity(ant *larva, ant *ent) const;
	double get_percentage(char type) const;
	void pass_day() const;
	~nest();
};
