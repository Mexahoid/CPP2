#include "stdafx.h"
#include "Queen.h"

Queen::Queen(int hunger, Nest *nest) : ant(hunger)
{
	power = nest->getQueenInfo();

}

void Queen::AskForEvolve(ant *larva)
{

}

