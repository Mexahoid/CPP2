#pragma once
#include "Entity.h"
#include "Nest.h"

class slave : public ant
{
private:
	int power_;
public:
	slave(int hunger, int power);
	void act(nest *nest) const;
};
