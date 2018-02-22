#include "stdafx.h"
#include "Entity.h"
#include "Nest.h"

Entity::Entity(int hunger, Nest *nest)
{
	this->hunger = hunger;
	this->nest = nest;
}

void Entity::Eat()
{
	nest->UseResources(hunger);
}

void Entity::Act() {};