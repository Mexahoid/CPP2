#include "stdafx.h"
#include "queen.h"

queen::queen(const int hunger, const int health, nest *nest) : ant(hunger, health, nest)
{
	power = nest_->getQueenInfo();
}

void queen::AskForEvolve(ant *larva)
{

}

