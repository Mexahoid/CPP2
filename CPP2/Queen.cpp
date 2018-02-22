#include "stdafx.h"
#include "Queen.h"

Queen::Queen(int hunger, Nest *nest) : Entity(hunger, nest)
{
	power = nest->getQueenInfo();

}

void Queen::AskForEvolve(Entity *larva)
{

}

