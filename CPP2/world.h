#pragma once
#include "main_entities.h"
#include "larva.h"

class world
{
	enemy_list *_enemies;
	nest *_nest;
	bool first_main_phase();
	void attack_phase() const;
	bool second_main_phase();

	void incr_enemies(int count);
	void clear_enemy_list();
public:
	explicit world(starting_numbers st);
	~world();
	void untap_all() const;
	bool pass_day();
};

