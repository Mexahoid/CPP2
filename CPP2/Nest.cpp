#include "stdafx.h"
#include "Nest.h"


Nest::Nest(int max)
{
	foodMaxPlain = max;
	foodMax = max;
	foodQuantity = 0;
	q = new Queen(100, this);
	entities = new EntityList();
	entities->entity = (Entity *)q;
	entities->next = NULL;
}

void Nest::AddEntity(Entity *entity)
{
	EntityList *el = new EntityList();
	el->entity = entity;
	el->next = entities;
	entities = el;
}

void Nest::UseResources(int count)
{
	foodQuantity -= count;
}

void Nest::AddResources(int count)
{
	foodQuantity += count;
	if (foodQuantity > foodMax)
		foodQuantity = foodMax;
}

int Nest::getSlaveInfo() {
	return slavePower;
}

int Nest::getSoldierInfo() {
	return soldierPower;
}

int Nest::getOverseerInfo() {
	return overseerPower;
}

int Nest::getQueenInfo() {
	return queenPower;
}

void Nest::clearEnemies(int amount) {
	enemiesCount -= amount;
	if (enemiesCount < 0)
		enemiesCount = 0;
}

void Nest::ReplaceLarvaWithNewEntity(Entity *larva, Entity *ent)
{
	EntityList *el = entities;
	while (el != NULL && el->entity != larva)
	{
		el->entity->Act();
		el = el->next;
	}
}

void Nest::PassDay()
{
	EntityList *el = entities;
	while (el != NULL)
	{
		el->entity->Act();
		el = el->next;
	}

	foodMax = (1 + overseerCount * overseerPower) * foodMaxPlain;
}

Nest::~Nest()
{
	delete(q);
}
