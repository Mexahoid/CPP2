#pragma once
#include "entities.h"
#include "nest.h"

class larva : public ant
{
private:
	queen const *_q;
public:
	larva(queen const *q, nest *nest, bool is_inited = false);
	void act() override;
	void evolve();
};

