#pragma once
#include "main_entities.h"

class world
{
	enemy_list *enemies_;
	nest *nest_;
	void first_main_phase();
	void attack_phase();
	void second_main_phase();

	void incr_enemies(int count);
	void clear_enemy_list();
public:
	explicit world(starting_numbers st);
	~world();
	void pass_day();
};

