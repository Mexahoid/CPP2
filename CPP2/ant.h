#pragma once
#include "entities.h"

class ant
{
protected:
	nest *nest_;

	int max_health_ = 0;
	int health_ = 0;
	int hunger_ = 0;
	int power_ = 0;

	int heal_amount_ = 0;
	char type_ = 5;
public:
	explicit ant(nest *nest, entity_data ed);
	virtual void act();
	bool is_alive() const;
	void hit(int amount);
	char get_type() const;
	void heal();
};

