#pragma once
#include "Entities.h"

extern class Entity
{
protected:
	Nest * nest;
	int hunger;
public:
	Entity(int hunger, Nest *nest);
	void Eat();
	void Act();
};

