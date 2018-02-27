#pragma once
#include "Entities.h"

class ant
{
protected:
	int hunger_;
	Nest *nest_;
	int health_;
public:
	explicit ant(int hunger, int health, Nest *nest);
	void act() const;
	bool is_alive() const;
};

