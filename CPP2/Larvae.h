#pragma once
#include "ant.h"
#include "Nest.h"
#include "Queen.h"

class larvae : public ant
{
private:
	int time_before_evolving_;
	int (*queen_api_)();
public:
	larvae(int hunger, int(*queen_method)(), Nest *nest);
	void act();
	void evolve() const;
};

