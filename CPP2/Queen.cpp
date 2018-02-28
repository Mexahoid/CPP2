#include "stdafx.h"
#include "Queen.h"

Queen::Queen(int hunger, nest *nest) : ant(hunger)
{
	power = nest->getQueenInfo();

}

void Queen::AskForEvolve(ant *larva)
{

}

