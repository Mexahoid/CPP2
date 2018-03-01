#pragma once

const int QUEEN_HUNGER = 1000;
const int SOLDIER_HUNGER = 100;
const int OVERSEER_HUNGER = 50;
const int SLAVE_HUNGER = 25;
const int LARVA_HUNGER = 10;

const int QUEEN_POWER = 100;
const int SOLDIER_POWER = 100;
const int OVERSEER_POWER = 100;
const int SLAVE_POWER = 100;
const int LARVAE_TIME = 15;



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

