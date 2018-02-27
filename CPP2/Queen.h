#pragma once
#include "ant.h"
#include "Nest.h"

class Queen : public ant
{
private:
	int power;
public:
	Queen(int hunger, Nest *nest);
	void AskForEvolve(ant *larva);
};


