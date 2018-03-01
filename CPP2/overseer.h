#pragma once
#include "entities.h"
#include "nest.h"

class overseer : public ant
{
public:
	overseer(nest *nest);
	void act() override;
	~overseer();
};

