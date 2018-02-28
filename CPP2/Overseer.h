#pragma once
#include "ant.h"

class overseer : public ant
{
public:
	overseer(int hunger, int health, Nest *nest);
	~overseer();
};

