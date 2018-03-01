#pragma once
#include "entities.h"
#include "nest.h"

class overseer : public ant
{
private:
	int power_;
public:
	overseer(int hunger, int health, nest *nest);
	~overseer();
};

