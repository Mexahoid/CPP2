#pragma once
#include "ant.h"
#include "Entities.h"

class overseer : public ant
{
public:
	overseer(int hunger, int health, nest *nest);
	~overseer();
};

