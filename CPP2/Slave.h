#pragma once
#include "ant.h"
#include "nest.h"

class slave : public ant
{
private:
	int power_;
public:
	slave(int hunger, int health, nest *nest);
	void act() const;
};
