#pragma once
class entity
{
protected:
	int health_;
	int max_health_;
	int hunger_;
	int heal_amount_;
	bool turned_;
public:
	virtual ~entity() = default;
	entity();
	entity(int health, int hunger, int healing);
	virtual void hit(int damage);
	virtual void heal();
	int get_health() const;
	virtual bool is_alive();
	virtual void turn();
	bool is_turned() const;
};

