#pragma once
#include "entities.h"
#include "nest.h"

class larvae : public ant
{
private:
	queen const *q_;
public:
	larvae(queen const *q, nest *nest, bool is_inited);
	void act() override;
	void evolve();
};

