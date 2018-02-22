#pragma once
#include "Entities.h"
#include "Nest.h"

class Soldier : public Entity
{
private:
	int power;
public:
	Soldier(int hunger, Nest *nest);
	void Act();
};
