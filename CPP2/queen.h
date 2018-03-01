#pragma once
#include "ant.h"
#include "nest.h"

class queen : public ant
{
private:
	int power_;
public:
	queen(int hunger, int health, nest *nest);
	void ask_for_evolve(ant *larva);
};


