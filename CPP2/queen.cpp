#include "stdafx.h"
#include "queen.h"

queen::queen(const int hunger, const int health, nest *nest) : ant(hunger, health, nest)
{
	type_ = 0;
	power_ = nest_->get_queen_info();
}

void queen::ask_for_evolve(ant *larva)
{

}

