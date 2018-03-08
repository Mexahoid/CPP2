#pragma once


typedef struct entity_data{
	int health;
	int healing;
	int hunger;
	int damage;
} entity_data;


class entity
{
protected:

	int _health;
	int _max_health;
	int _heal_amount;

	int _hunger;
	int _damage;

	bool _tapped;
public:
	virtual ~entity();
	entity();
	explicit entity(entity_data data);
	virtual void hit(int damage);
	int get_damage() const;
	virtual void heal();
	int get_health() const;
	virtual bool is_alive();
	virtual void tap();
	virtual void untap();
	bool is_tapped() const;
};

