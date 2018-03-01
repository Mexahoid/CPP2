#pragma once
#include "ant.h"
#include "nest.h"

class queen : public ant
{
private:
	int power;
public:
	queen(int hunger, int health, nest *nest);
	void AskForEvolve(ant *larva);
};


