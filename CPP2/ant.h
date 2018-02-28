#pragma once
#include "Entities.h"

class ant
{
protected:
	int hunger_;
	nest *nest_;
	int health_;
public:
	explicit ant(int hunger, int health, nest *nest);
	void act() const;
	bool is_alive() const;
};

