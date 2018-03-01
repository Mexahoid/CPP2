#pragma once
#include "entities.h"
#include "nest.h"

class slave : public ant
{
public:
	slave(nest *nest);
	void act() override;
};
