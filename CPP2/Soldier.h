#pragma once
#include "entities.h"
#include "nest.h"

class soldier : public ant
{
private:
	int power_;
public:
	soldier(int hunger, int health, nest *nest);
	void act() const;
};
