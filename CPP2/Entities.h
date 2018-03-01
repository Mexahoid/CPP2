#pragma once

const int QUEEN_HEALTH = 1000;
const int QUEEN_HUNGER = QUEEN_HEALTH / 5 * 2;
const int QUEEN_POWER = QUEEN_HEALTH / 100;
const int QUEEN_HEAL = QUEEN_HEALTH / 10;

const int SOLDIER_HEALTH = 500;
const int SOLDIER_HUNGER = SOLDIER_HEALTH / 5;
const int SOLDIER_POWER = SOLDIER_HEALTH / 100 * 5;
const int SOLDIER_HEAL = SOLDIER_HEALTH / 5;

const int OVERSEER_HEALTH = 100;
const int OVERSEER_HUNGER = OVERSEER_HEALTH / 2;
const int OVERSEER_POWER = OVERSEER_HEALTH / 100 * 4;
const int OVERSEER_HEAL = OVERSEER_HEALTH / 4;

const int SLAVE_HEALTH = 50;
const int SLAVE_HUNGER = SLAVE_HEALTH / 5 * 2;
const int SLAVE_POWER = SLAVE_HEALTH * 2;
const int SLAVE_HEAL = SLAVE_HEALTH / 10;

const int LARVAE_HEALTH = 5;
const int LARVAE_HUNGER = LARVAE_HEALTH * 2;
const int LARVAE_TIME = LARVAE_HEALTH * 2;
const int LARVAE_HEAL = LARVAE_HEALTH / 5;

const int ENEMIES_INCOME_COUNT_MAX = 15;
const int ENEMIES_POWER_MAX = 3;

class ant;
class queen;
class soldier;
class overseer;
class slave;
class larvae;
class nest;


typedef struct entity_list {
	ant *entity;
	entity_list *next;
} entity_list;

typedef struct entity_data
{
	int health;
	int hunger;
	int power;
	char type;
	int healing;
} entity_data;
