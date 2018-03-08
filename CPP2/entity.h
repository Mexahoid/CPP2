#pragma once
#include <string>


typedef struct entity_data{
	int health;
	int healing;
	int hunger;
	int damage;
} entity_data;

typedef void(*messenger)(const char *, bool);

class entity
{
protected:

	void send_hit_message(char type, int damage) const;
	int _health;
	int _max_health;
	int _heal_amount;
	char _type = 5;

	messenger _messenger;
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
	char get_type() const;
};

