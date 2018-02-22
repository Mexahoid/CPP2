#pragma once
#include "Entity.h"
#include "Nest.h"

class Slave : public Entity
{
private:
	int power;
public:
	Slave(int hunger, Nest *nest);
	void Act();
};
