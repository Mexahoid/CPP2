#pragma once
#include "consts.h"
#include "main_entities.h"


class ant;
class queen;
class soldier;
class overseer;
class slave;
class larvae;


typedef struct ant_list {
	ant *entity;
	ant_list *next;
} ant_list;

typedef struct ant_data
{
	int health;
	int hunger;
	int power;
	char type;
	int healing;
} ant_data;
