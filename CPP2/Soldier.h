#pragma once
#include "entities.h"
#include "nest.h"

class soldier : public ant
{
public:
	soldier(nest *nest);
	void act() override;
};
