#include "stdafx.h"
#include "Nest.h"


nest::nest(int max)
{
	foodMaxPlain = max;
	foodMax = max;
	foodQuantity = 0;
	q = new Queen(100, this);
	entities = new EntityList();
	entities->entity = (ant *)q;
	entities->next = NULL;
}

void nest::overseer_increase(int power)
{
}

void nest::overseer_decrease(int power)
{
}

void nest::AddEntity(ant *entity)
{
	EntityList *el = new EntityList();
	el->entity = entity;
	el->next = entities;
	entities = el;
}

void nest::UseResources(int count)
{
	foodQuantity -= count;
}

void nest::AddResources(int count)
{
	foodQuantity += count;
	if (foodQuantity > foodMax)
		foodQuantity = foodMax;
}

int nest::getSlaveInfo() {
	return slavePower;
}

int nest::getSoldierInfo() {
	return soldierPower;
}

int nest::getOverseerInfo() {
	return overseerPower;
}

int nest::getQueenInfo() {
	return queenPower;
}

void nest::clearEnemies(int amount) {
	enemiesCount -= amount;
	if (enemiesCount < 0)
		enemiesCount = 0;
}

void nest::ReplaceLarvaWithNewEntity(ant *larva, ant *ent)
{
	EntityList *el = entities;
	while (el && el->entity != larva)
	{
		el->entity->act();
		el = el->next;
	}
}

void nest::PassDay()
{
	EntityList *el = entities;
	while (el != NULL)
	{
		el->entity->act();
		el = el->next;
	}

	foodMax = (1.0 + overseerCount * overseerPower / 100) * foodMaxPlain;
}

nest::~nest()
{
	delete(q);
}
