#pragma once

class nest;
class entity;
class enemy;

typedef struct
{
	int food_max;
	int food_current;
	int soldier_count;
	int overseer_count;
	int slave_count;
	int larvae_count;
} starting_numbers;

typedef struct enemy_list {
	enemy *enemy;
	enemy_list *next;
} enemy_list;
