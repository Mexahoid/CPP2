#pragma once
#include "Entities.h"
#include "Entity.h"
#include "Queen.h"
#include "Larvae.h"
#include "Soldier.h"
#include "Slave.h"

const int QUEEN_HUNGER = 1000;
const int SOLDIER_HUNGER = 100;
const int OVERSEER_HUNGER = 50;
const int SLAVE_HUNGER = 25;
const int LARVA_HUNGER = 10;

typedef struct EntityList {
	Entity *entity;
	EntityList *next;
} EntityList;


extern class Nest
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
	double overseerPower;
	int slavePower;

	int soldierCount;
	int overseerCount;
	int slaveCount;
	int larvaCount;

public:
	Nest(int max);
	void AddEntity(Entity *entity);
	void UseResources(int count);
	void AddResources(int count);
	int getSlaveInfo();
	int getSoldierInfo();
	int getOverseerInfo();
	int getQueenInfo();
	void clearEnemies(int amount);
	void ReplaceLarvaWithNewEntity(Entity *larva, Entity *ent);
	void PassDay();
	~Nest();
};
