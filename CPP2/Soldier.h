#pragma once
#include "Entities.h"
#include "Nest.h"

class soldier : public ant
{
private:
	int power_;
public:
	soldier(int hunger, int health, nest *nest);
	void act() const;
};
