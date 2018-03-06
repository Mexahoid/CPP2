#include "stdafx.h"
#include "queen.h"
#include <ctime>
#include <cstdlib>

queen::queen(nest *const nest) : ant(nest, nest->get_info(0))
{
	turned_ = false;
}

void queen::ask_for_evolve() const
{
	char type = 1;
	double percentage[] = { 0, 0, 0 };
	for (type = 0; type < 3; type++)
	{
		percentage[type] = nest_->get_percentage(type + 1);
	}

	percentage[0] *= SOLDIER_MULT;
	percentage[1] *= OVERSEER_MULT;
	percentage[2] *= SLAVE_MULT;

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
	// ���� �� ��������
	if (health_ < 1)
	{
		death_reason_ = false;
		return;
	}

	// ������� ����������� ������
	if (!turned_)
		ant::act();
	
	// ����� ����� �� ������� ���, ���� ���������
	if (health_ < 1)
	{
		death_reason_ = true;
		return;
	}

	// ���� ���������, �� �� �� ������ 
	// ��� ������ ���� ����
	if (turned_ && health_ <= max_health_ - heal_amount_)
		ant::act();

	// ���� ������� ��� ������ 30%, �� ����������� � �����
	// �.�. ���� � ������ ���� ���� �������� �� �����
	if (nest_->get_percentage(4) > 0.3)
	{
		turned_ = true;
		return;
	}

	// ���� ������� ������ � ��� �� ���������
	// ����� ��������� ��� � ������, ��� � �� ������ ���� ����
	if (!turned_)
	{
		srand(time(nullptr));
		const int spawning = rand() % power_;
		for (int i = 0; i < spawning; i++)
		{
			larvae *lv = new larvae(this, nest_, false);
			nest_->add_new_ant(lv);
		}
		turned_ = true;
	}
}

bool queen::get_death_reason() const
{
	return death_reason_;
}
