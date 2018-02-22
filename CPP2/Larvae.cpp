#include "stdafx.h"
#include "Larvae.h"
#include "Nest.h"


Larvae::Larvae(int hunger, Queen *queen, Nest *nest) : Entity(hunger, nest)
{
	q = queen;
}

void Larvae::Act()
{
	nest->UseResources(hunger);
	timeBeforeEvolving--;
	if (timeBeforeEvolving == 0)
		Evolve();
}

void Larvae::Evolve()
{
	q->AskForEvolve(this);
}