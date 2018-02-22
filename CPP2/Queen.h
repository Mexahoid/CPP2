#pragma once
#include "Entity.h"
#include "Nest.h"

class Queen : public Entity
{
private:
	int power;
public:
	Queen(int hunger, Nest *nest);
	void AskForEvolve(Entity *larva);
};


