#pragma once
#include "Entities.h"
#include "ant.h"
#include "Queen.h"
#include "Larvae.h"
#include "Soldier.h"
#include "Slave.h"

const int QUEEN_HUNGER = 1000;
const int SOLDIER_HUNGER = 100;
const int OVERSEER_HUNGER = 50;
const int SLAVE_HUNGER = 25;
const int LARVA_HUNGER = 10;

const int LARVAE_TIME = 15;

typedef struct EntityList {
	ant *entity;
	EntityList *next;
} EntityList;


class Nest
{
private:
	Queen * q;
	EntityList *entities;
	int foodQuantity;

	int foodMaxPlain;
	int foodMax;

	int enemiesCount;

	int queenPower;
	int soldierPower;
	int overseerPower;
	int slavePower;

	int soldierCount;
	int overseerCount;
	int slaveCount;
	int larvaCount;

public:
	Nest(int max);
	void overseer_increase(int power);
	void overseer_decrease(int power);
	void AddEntity(ant *entity);
	void UseResources(int count);
	void AddResources(int count);
	int getSlaveInfo();
	int getSoldierInfo();
	int getOverseerInfo();
	int getQueenInfo();
	void clearEnemies(int amount);
	void ReplaceLarvaWithNewEntity(ant *larva, ant *ent);
	void PassDay();
	~Nest();
};
