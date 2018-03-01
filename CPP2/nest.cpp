#include "stdafx.h"
#include "nest.h"


nest::nest(const int max)
{
	food_max_default_ = max;
	food_max_ = max;
	food_quantity_ = 0;
	queen * q = new queen(100, 1000, this);
	entities_ = new entity_list();
	entities_->entity = static_cast<ant *>(q);
	entities_->next = NULL;
}

void nest::overseer_increase(const int power)
{
	food_max_ += food_max_default_ * power / 100;
}

void nest::overseer_decrease(const int power)
{
	food_max_ -= food_max_default_ * power / 100;
}

void nest::add_entity(ant *entity)
{
	entity_list *el = new entity_list();
	el->entity = entity;
	el->next = entities_;
	entities_ = el;
}

void nest::use_resources(const int count)
{
	food_quantity_ -= count;
}

void nest::add_resources(const int count)
{
	food_quantity_ += count;
	if (food_quantity_ > food_max_)
		food_quantity_ = food_max_;
}

int nest::get_slave_info() const
{
	return slave_power_;
}

int nest::get_soldier_info() const
{
	return soldier_power_;
}

int nest::get_overseer_info() const
{
	return overseer_power_;
}

int nest::get_queen_info() const
{
	return queen_power_;
}

void nest::clear_enemies(const int amount) {
	enemies_count_ -= amount;
	if (enemies_count_ < 0)
		enemies_count_ = 0;
}

void nest::replace_larva_with_new_entity(ant *larva, ant *ent) const
{
	entity_list *el = entities_;
	while (el && el->entity != larva)
	{
		el->entity->act();
		el = el->next;
	}
}

void nest::pass_day() const
{
	entity_list *el = entities_;
	while (el)
	{
		el->entity->act();
		if(!el->next->entity->is_alive())
		{
			entity_list *d = el->next;
			el->next = el->next->next;
			delete d->entity;
			delete d;
		}
		el = el->next;
	}
}

double nest::get_percentage(const char type) const
{
	int count = 0;
	int needed_type_count = 0;

	entity_list *el = entities_;
	while (el)
	{
		count++;
		if (el->entity->get_type() == type)
			needed_type_count++;
		el = el->next;
	}

	return needed_type_count * 1.0 / count;
}

nest::~nest()
{
	entity_list *el = entities_;
	while (el)
	{
		entity_list *d = el;
		el = el->next;
		delete d->entity;
		delete d;
	}

	delete el;
}
