#pragma once
#include "ant.h"
#include "nest.h"
#include "queen.h"

class larvae : public ant
{
private:
	int time_before_evolving_;
	int (*ask_queen_for_evolving_)();
public:
	larvae(int hunger, int health, int(*queen_method)(), nest *nest);
	void act();
	void evolve();
};

