#pragma once
class entity
{
protected:
	int health_;
	int max_health_;
	int hunger_;
	int heal_amount_;
public:
	entity(int health, int hunger, int healing);
	virtual void hit(int damage);
	virtual void heal();
	virtual int get_health();
};

