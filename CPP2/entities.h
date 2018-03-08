#pragma once
#include "consts.h"
#include "main_entities.h"
#include "entity.h"


class ant;
class queen;
class soldier;
class overseer;
class slave;
class larva;


typedef struct ant_list {
	ant *entity;
	ant_list *next;
} ant_list;

typedef struct ant_data
{
	entity_data ed;
	int power;
	char type;
} ant_data;
