#include "stdafx.h"
#include "queen.h"

queen::queen(nest *const nest) : ant(nest, nest->get_info(0))
{
}

void queen::ask_for_evolve() const
{
	char type = 1;
	double percentage[] = { 0, 0, 0};
	for (type = 0; type < 3; type++)
	{
		percentage[type] = nest_->get_percentage(type + 1);
	}
	double min = 0xffffffff;
	char lesser_type = 1;
	for (type = 0; type < 3; type++)
	{
		if (percentage[type] < min)
		{
			min = percentage[type];
			lesser_type = type;
		}
	}
	switch (lesser_type + 1)
	{
	case 1:
		nest_->add_new_ant(new soldier(nest_));
		break;
	case 2:
		nest_->add_new_ant(new overseer(nest_));
		break;
	case 3:
		nest_->add_new_ant(new slave(nest_));
		break;
	default:
		break;
	}
}

void queen::act()
{
	ant::act();
	for (int i = 0; i < power_; i++)
	{
		larvae *lv = new larvae(this, nest_);
		nest_->add_new_ant(lv);
	}
}
