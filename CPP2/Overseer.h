#pragma once
#include "ant.h"

class overseer : public ant
{
public:
	overseer(int hunger, Nest *nest);
	~overseer();
};

