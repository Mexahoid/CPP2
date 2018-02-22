#pragma once
#include "Entity.h"
#include "Nest.h"
#include "Queen.h"

class Larvae : public Entity
{
private:
	Queen * q;
	int timeBeforeEvolving;
public:
	Larvae(int hunger, Queen *queen, Nest *nest);
	void Act();
	void Evolve();
};

