#pragma once
#include "entities.h"
#include "soldier.h"
#include "overseer.h"
#include "slave.h"
#include "larvae.h"
#include "nest.h"

class queen : public ant
{
private:
	bool death_reason_ = false;
public:
	queen(nest *nest);
	void ask_for_evolve() const;
	void act() override;
	bool get_death_reason() const;
};


